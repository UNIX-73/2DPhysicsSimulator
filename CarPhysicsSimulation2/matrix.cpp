#include "Matrix.h"
#include <stdexcept>




// Constructor con lista de inicialización
Matrix::Matrix(const std::vector<std::vector<double>>& values) {
    if (values.empty()) {
        rows = 0;
        cols = 0;
        data.clear();
    }
    else {
        rows = values.size();
        cols = values[0].size();
        data = values;

        // Verifica si todas las filas tienen el mismo tamaño
        for (const auto& row : values) {
            if (row.size() != cols) {
                throw std::invalid_argument("Todas las filas deben tener el mismo número de columnas.");
            }
        }
    }
}
// Constructor para matriz vacía
Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<double>(cols, 0.0));
}



// Obtener un valor en una posición

double& Matrix::operator()(size_t row, size_t col) {
    if (row >= rows || col >= cols) throw std::out_of_range("Índice fuera de rango");
    return data[row][col];
}

const double& Matrix::operator()(size_t row, size_t col) const {
    if (row >= rows || col >= cols) throw std::out_of_range("Índice fuera de rango");
    return data[row][col];
}


void Matrix::PushRowBack(const std::vector<double>& row)
{
    if (row.size() == cols)
    {
        data.push_back(row);
        ++rows;
    }
    else
    {
        std::cout << "Se está intentando añadir una fila con un tamaño distinto al de la matriz" << std::endl;
    }
}

void Matrix::PushColBack(const std::vector<double>& col)
{
    size_t lastCol = col.size();

    if (lastCol == rows)
    {
        int i = 0;

        for (auto& row : data)
        {
            row.push_back(col[i]);
        }

        ++cols;
    }
    else
    {
        std::cout << "Se está intentando añadir una columna con un tamaño distinto al de la matriz" << std::endl;
    }
}

void Matrix::SetValue(int rowIdx, int colIdx, const double value)
{
    // Verifica que los índices estén dentro del rango válido
    if (rowIdx >= 0 && rowIdx < static_cast<int>(rows) &&
        colIdx >= 0 && colIdx < static_cast<int>(cols))
    {
        data[rowIdx][colIdx] = value;
    }
    else
    {
        std::cout << "Error: Índice fuera de rango. Índices proporcionados: fila "
            << rowIdx << ", columna " << colIdx << ". Rango válido es [0, "
            << rows - 1 << "] para filas y [0, " << cols - 1 << "] para columnas."
            << std::endl;
    }
}


// Es como usar un += para un valor específico de la matriz
void Matrix::AddValue(int rowIdx, int colIdx, const double value)
{
    // Verifica que los índices estén dentro del rango válido
    if (rowIdx >= 0 && rowIdx < static_cast<int>(rows) &&
        colIdx >= 0 && colIdx < static_cast<int>(cols))
    {
        data[rowIdx][colIdx] += value;
    }
    else
    {
        std::cout << "Error: Índice fuera de rango. Índices proporcionados: fila "
            << rowIdx << ", columna " << colIdx << ". Rango válido es [0, "
            << rows - 1 << "] para filas y [0, " << cols - 1 << "] para columnas."
            << std::endl;
    }
}

void Matrix::SetRow(int rowIdx, const std::vector<double>& row)
{
    if (0 <= rowIdx && rowIdx < rows)
    {
        if (row.size() == cols)
        {
            data[rowIdx] = row;
        }
        else
        {
            std::cout << "Error: Tamaño de la fila incorrecto. Fila proporcionada tiene "
                << row.size() << " elementos, pero se esperaba " << cols << " elementos."
                << std::endl;
        }
    }
    else
    {
        std::cout << "Error: Índice de fila fuera de rango. Índice proporcionado: "
            << rowIdx << ", pero el rango válido es [0, " << rows - 1 << "]."
            << std::endl;
    }
}

Matrix Matrix::AdjustSize(const Matrix& smaller, size_t newRows)
{
    Matrix result(newRows, smaller.getCols());
    // Copiar valores de la matriz original
    for (size_t i = 0; i < smaller.getRows(); ++i) {
        for (size_t j = 0; j < smaller.getCols(); ++j) {
            result.SetValue(i, j, smaller.getValue(i, j));
        }
    }
    // Añadir ceros a las filas adicionales
    for (size_t i = smaller.getRows(); i < newRows; ++i) {
        for (size_t j = 0; j < smaller.getCols(); ++j) {
            result.SetValue(i, j, 0.0);
        }
    }
    return result;
}

void Matrix::appendColumn(const Matrix& colMatrix)
{
    if (colMatrix.getCols() != 1 || colMatrix.getRows() != this->getRows()) {
        throw std::invalid_argument("La columna debe tener 1 columna y el mismo número de filas que la matriz original.");
    }

    // Crear una nueva matriz con una columna adicional
    Matrix newMatrix(this->getRows(), this->getCols() + 1);

    // Copiar los valores de la matriz original
    for (int i = 0; i < this->getRows(); i++) {
        for (int j = 0; j < this->getCols(); j++) {
            newMatrix(i, j) = this->operator()(i, j);
        }
    }

    // Añadir la nueva columna
    for (int i = 0; i < colMatrix.getRows(); i++) {
        newMatrix(i, this->getCols()) = colMatrix.getValue(i, 0);  // Añadir los valores de la nueva columna
    }

    // Actualizar los datos de la matriz actual con la nueva matriz
    *this = newMatrix;
}

void Matrix::swapRows(int row1, int row2)
{
    if (row1 >= this->getRows() || row2 >= this->getRows()) {
        throw std::out_of_range("Los índices de fila están fuera de rango.");
    }

    for (int j = 0; j < this->getCols(); j++) {
        std::swap(this->operator()(row1, j), this->operator()(row2, j));
    }
}

void Matrix::resize(size_t newRows, size_t newCols)
{
    data.resize(newRows);

    // Redimensionar las columnas en cada fila
    for (int i = 0; i < newRows; ++i) {
        data[i].resize(newCols, 0);  // Llena con ceros los nuevos elementos si es necesario
    }

    // Actualizar el número de filas y columnas
    rows = newRows;
    cols = newCols;
}


// Obtener dimensiones
size_t Matrix::getRows() const { return rows; }
size_t Matrix::getCols() const { return cols; }

double Matrix::getValue(int row, int col) const
{
    return data[row][col];
}

// Suma de matrices
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Dimensiones incompatibles para la suma");

    Matrix result(this->rows, this->cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Resta de matrices
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Dimensiones incompatibles para la resta");

    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-() const
{
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            result.data[i][j] = -data[i][j];
        }
    }

    return result;
}

// Multiplicación de matrices
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Dimensiones incompatibles para la multiplicación");

    Matrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                result(i, j) += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(const double& other) const
{
    // Crear una nueva matriz con el mismo tamaño que la original
    Matrix result(rows, cols);

    // Recorrer cada fila
    for (int i = 0; i < rows; ++i)
    {
        // Recorrer cada columna
        for (int j = 0; j < cols; ++j)
        {
            // Multiplicar cada elemento de la matriz por el escalar
            result.SetValue(i, j, this->getValue(i, j) * other);
        }
    }

    return result;
}

// Transposición de la matriz
Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(j, i) = data[i][j];
        }
    }
    return result;
}

// Multiplicación de matriz por un vector
std::vector<double> Matrix::operator*(const std::vector<double>& vec) const {
    if (cols != vec.size())
        throw std::invalid_argument("Dimensiones incompatibles para multiplicar matriz por vector");

    std::vector<double> result(rows, 0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i] += data[i][j] * vec[j];
        }
    }
    return result;
}

// Mostrar matriz
void Matrix::print() const {
    std::cout << "Filas: " << rows << ", Columnas: " << cols << std::endl;
    for (const auto& row : data) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

