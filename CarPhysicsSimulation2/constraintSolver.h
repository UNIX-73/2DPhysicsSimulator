#pragma once
#include "constraint.h"
#include "physicsState.h"
#include "matrix.h"
#include <vector>
#include <tuple>

class ConstraintSolver
{
public:
	ConstraintSolver();
	
	~ConstraintSolver() = default;


	void AddConstraint(std::shared_ptr<Constraint>& constraint);
	void RemoveConstraint(std::shared_ptr<Constraint>& constraint);


	void SolveConstraints(double step);


	void PrintW();
	void PrintQ();
	void PrintJ();
	void Print_q_dot();


private:
	std::vector<std::shared_ptr<Constraint>> constraints;

	std::vector<std::tuple<int, std::shared_ptr<PhysicsState>>> statesIndex;

	Matrix J = Matrix(0, 0);
	Matrix Q = Matrix(0, 0);
	Matrix W = Matrix(0, 0);
	Matrix q_dot = Matrix(0, 0);


	void StateIndexes();

	int GetStateIdx(std::shared_ptr<PhysicsState> state);

	void UpdateMatrixVariables();

	void CreateW();

	void Create_q_dot();

	void CreateJacobianAndQ(double step);

	void CholeskySolver(const Matrix& A, const Matrix& B, Matrix* lambda);

	void ApplyConstraintForces(const Matrix& lambda);
};