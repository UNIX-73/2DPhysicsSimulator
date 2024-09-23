#include "constraintSolver.h"

#include <string>

void ConstraintSolver::SolveConstraints()
{
    StateIndexes();
    CreateW();
    CreateJacobianAndQ();
    Create_q_dot();

    //  Left
    Matrix JWJT = J * W * J.transpose();

    //  Right
    Matrix Jq = J * q_dot;
    Matrix JWQ = J * W * Q;

    Matrix _Jq_JWQ = -Jq - JWQ;

    Matrix result(_Jq_JWQ.getRows(), size_t(1));


    Matrix A = Matrix({ {4.0, 2.0},
                        {2.0, 3.0} });

    std::vector<std::vector<double>> bVector{ { 10.0 }, { 11.0 } };

    Matrix B = Matrix(bVector);


    CholeskySolver(A, B, &result);

    result.print();
}

void ConstraintSolver::CholeskySolver(const Matrix& A, const Matrix& B, Matrix* result)
{
    // Verificamos que A sea cuadrada y que B tenga dimensiones compatibles.
    if (A.getRows() != A.getCols()) {
        throw std::invalid_argument("La matriz A debe ser cuadrada.");
    }

    int n = A.getRows();

    // Inicializar la matriz L como triangular inferior de tamaño nxn
    Matrix L(n, n);

    // Descomposición de Cholesky para obtener L
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = 0.0;

            if (i == j) {  // Elementos de la diagonal
                for (int k = 0; k < j; ++k) {
                    sum += L(i, k) * L(i, k);
                }
                L(i, i) = std::sqrt(A.getValue(i, i) - sum);
            }
            else {  // Elementos fuera de la diagonal
                for (int k = 0; k < j; ++k) {
                    sum += L(i, k) * L(j, k);
                }
                L(i, j) = (A.getValue(i, j) - sum) / L(j, j);
            }
        }
    }

    // Ahora resolvemos el sistema Ly = B mediante sustitución hacia adelante
    Matrix y(n, B.getCols());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < B.getCols(); ++j) {
            double sum = 0.0;
            for (int k = 0; k < i; ++k) {
                sum += L(i, k) * y(k, j);
            }
            y(i, j) = (B.getValue(i, j) - sum) / L(i, i);
        }
    }

    // Luego resolvemos L^T x = y mediante sustitución hacia atrás
    Matrix& x = *result;
    x.resize(n, B.getCols());

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < B.getCols(); ++j) {
            double sum = 0.0;
            for (int k = i + 1; k < n; ++k) {
                sum += L(k, i) * x(k, j);
            }
            x(i, j) = (y(i, j) - sum) / L(i, i);
        }
    }
}


void ConstraintSolver::PrintW()
{
    W.print();
}

void ConstraintSolver::PrintQ()
{
    Q.print();
}

void ConstraintSolver::PrintJ()
{
    J.print();
}

void ConstraintSolver::Print_q_dot()
{
    q_dot.print();
}

void ConstraintSolver::StateIndexes()
{
    statesIndex.clear();

    int i = 0;
    int constrainedAxis = 0;

    for (const auto constraint : constraints)
    {
        // Obtener objA y objB desde el constraint
        std::shared_ptr<PhysicsState> objA = constraint->GetObjA();
        std::shared_ptr<PhysicsState> objB = constraint->GetObjB();

        // Función lambda para buscar un objeto en el vector physicsIndex
        auto objectExistsInIndex = [&](std::shared_ptr<PhysicsState> obj) -> bool {
            for (const auto& entry : statesIndex) {
                if (std::get<1>(entry) == obj) {
                    return true; // El objeto ya está en el índice
                }
            }
            return false; // El objeto no está en el índice
            };

        // Si objA no está, añadirlo
        if (!objectExistsInIndex(objA)) {
            statesIndex.push_back(std::make_tuple(i++, objA));
        }

        // Si objB no está, añadirlo
        if (!objectExistsInIndex(objB)) {
            statesIndex.push_back(std::make_tuple(i++, objB));
        }
    }


    //Establecer tamaño de las matrices
    
    if (!statesIndex.empty())
    {
        size_t numStates = statesIndex.size(); // Número total de estados (objetos)
        size_t wSize = numStates * 3; // Cada estado tiene 3 grados de libertad (x, y, Ø)

        W = Matrix(wSize, wSize); // Inicializar la matriz W como wSize x wSize
        Q = Matrix(wSize, 1);
        J = Matrix(0, wSize); //se añaden luego las rows
        q_dot = Matrix(wSize, 1);
    }
 

}

int ConstraintSolver::GetStateIdx(std::shared_ptr<PhysicsState> state)
{
    for (const auto stateIdx : statesIndex)
    {
        if (std::get<1>(stateIdx) == state) return std::get<0>(stateIdx);
    }

    std::cout << "No se encontró el state, parece haber un error en el sistema de constraintSolver" << std::endl;

    return 0;
}

void ConstraintSolver::CreateW()
{
    int maxCols = 0;

    if (!statesIndex.empty())
    {
        maxCols = (std::get<0>(statesIndex.back()) + 1) * 3; // * 3 porque hay 3 grados de movimiento (x, y, Ø), +1 porque empieza por 0
    }
    else
    {
        std::cout << "No hay constraints añadidos" << std::endl;
        return;
    }

    int currentRow = 0;

    for (const auto& state : statesIndex)
    {
        int i = std::get<0>(state);

        std::vector<double> rowX(maxCols, 0.0);
        std::vector<double> rowY(maxCols, 0.0);
        std::vector<double> rowØ(maxCols, 0.0);

        rowX[i * 3] = std::get<1>(state)->invMass;
        rowY[i * 3 + 1] = std::get<1>(state)->invMass;
        rowØ[i * 3 + 2] = std::get<1>(state)->invInertia;

        W.SetRow(currentRow++, rowX);
        W.SetRow(currentRow++, rowY);
        W.SetRow(currentRow++, rowØ);
    }
}

void ConstraintSolver::Create_q_dot()
{
    int idx = 0;

    for (const auto& state : statesIndex)
    {
        q_dot.SetValue(idx++, 0, std::get<1>(state)->wVel.x);
        q_dot.SetValue(idx++, 0, std::get<1>(state)->wVel.y);
        q_dot.SetValue(idx++, 0, std::get<1>(state)->wAngularVel);
    }
}



void ConstraintSolver::CreateJacobianAndQ()
{
    if (constraints.empty()) return;

    size_t wSize = statesIndex.size() * 3;

    for (const auto& constraint : constraints)
    {
        std::shared_ptr<PhysicsState> objA = constraint->GetObjA();
        std::shared_ptr<PhysicsState> objB = constraint->GetObjB();

        int idxA = GetStateIdx(objA);
        int idxB = GetStateIdx(objB);

        ConstraintResult res = constraint->SolveConstraint(step);

        // Q
        if (res.constraintsX)
        {
            Q.AddValue(idxA * 3, 0, res.QxA);
            Q.AddValue(idxB * 3, 0, res.QxB);
        }
        
        if (res.constraintsY)
        {
            Q.AddValue(idxA * 3 + 1, 0, res.QyA);
            Q.AddValue(idxB * 3 + 1, 0, res.QyB);
        }

        if (res.constraintsØ)
        {
            Q.AddValue(idxA * 3 + 2, 0, res.QØA);
            Q.AddValue(idxB * 3 + 2, 0, res.QØB);

            std::cout << std::to_string(res.QØB) << std::endl;
        }


        // J
        if (res.constraintsX)
        {
            std::vector<double> xRow(wSize, 0.0);

            xRow[idxA * 3] = res.JxA;
            xRow[idxB * 3] = res.JxB;

            J.PushRowBack(xRow);
        }
        if (res.constraintsY)
        {
            std::vector<double> yRow(wSize, 0.0);
            
            yRow[idxA * 3 + 1] = res.JyA;
            yRow[idxB * 3 + 1] = res.JyB;

            J.PushRowBack(yRow);
        }
        if (res.constraintsØ)
        {
            std::vector<double> ØRow(wSize, 0.0);

            ØRow[idxA * 3 + 2] = res.JØA;
            ØRow[idxB * 3 + 2] = res.JØB;

            J.PushRowBack(ØRow);
        }
    }
}
