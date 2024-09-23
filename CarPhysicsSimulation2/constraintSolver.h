#pragma once
#include "constraint.h"
#include "physicsState.h"
#include "matrix.h"
#include <vector>
#include <tuple>

class ConstraintSolver
{
public:
	ConstraintSolver(double step, std::vector<std::shared_ptr<Constraint>>& constraints) :
		step(step), constraints(constraints) {};
	~ConstraintSolver() = default;


	void SolveConstraints();

	void CholeskySolver(const Matrix& A, const Matrix& B, Matrix* result);

	void PrintW();
	void PrintQ();
	void PrintJ();
	void Print_q_dot();


private:
	std::vector<std::shared_ptr<Constraint>> constraints;
	double step;

	std::vector<std::tuple<int, std::shared_ptr<PhysicsState>>> statesIndex;

	Matrix J = Matrix(0, 0);
	Matrix Q = Matrix(0, 0);
	Matrix W = Matrix(0, 0);
	Matrix q_dot = Matrix(0, 0);


	void StateIndexes();

	int GetStateIdx(std::shared_ptr<PhysicsState> state);

	void CreateW();

	void Create_q_dot();

	void CreateJacobianAndQ();

};