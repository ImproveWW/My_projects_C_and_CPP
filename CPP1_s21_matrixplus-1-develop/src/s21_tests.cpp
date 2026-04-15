#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(TestCreate, CreateMatrix) { ASSERT_NO_THROW(S21Matrix matrix(3, 3)); }

TEST(TestCreate, CreateMatrixNegativeSize) {
  ASSERT_THROW(S21Matrix matrix(-3, 3), std::invalid_argument);
}

TEST(TestCopy, CopyMatrix) {
  S21Matrix A(3, 3);
  S21Matrix B(A);

  EXPECT_TRUE(A == B);
}

TEST(TestCopy, CopyMatrix2) {
  S21Matrix A(2, 2);
  S21Matrix B(A);
  ASSERT_NO_THROW(S21Matrix B(A));
}

TEST(TestMove, MoveMatrix) {
  S21Matrix A(4, 4);
  S21Matrix B(std::move(A));

  EXPECT_FALSE(A == B);
}

TEST(TestMove, MoveMatrix2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  S21Matrix B(std::move(A));

  EXPECT_FALSE(A == B);
  EXPECT_TRUE(B(0, 0) == 1);
  EXPECT_TRUE(B(0, 1) == 2);
  EXPECT_TRUE(B(1, 0) == 3);
  EXPECT_TRUE(B(1, 1) == 4);
}

TEST(TestEq, EqMatrix) {
  S21Matrix A;
  A(1, 1) = 2.4;
  A(1, 2) = 3.5;

  S21Matrix B;
  B(1, 1) = 2.4;
  B(1, 2) = 3.5;

  bool res = A.EqMatrix(B);
  bool res2 = B.EqMatrix(A);

  EXPECT_TRUE(res);
  EXPECT_TRUE(res2);
  EXPECT_TRUE(res = res2);
}

TEST(TestEq, EqMatrix2) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 2);

  bool res = A.EqMatrix(B);
  bool res2 = B.EqMatrix(A);
  EXPECT_FALSE(res);
  EXPECT_FALSE(res2);
  EXPECT_FALSE(res = res2);
}

TEST(TestEq, EqMatrix3) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.2, A(0, 1) = 2.3, A(0, 2) = 3.4;
  A(1, 0) = 4.5, A(1, 1) = 5.6, A(1, 2) = 6.7;
  A(2, 0) = 7.8, A(2, 1) = 8.9, A(2, 2) = 9.0;

  S21Matrix B(3, 3);
  B(0, 0) = 1.2, B(0, 1) = 2.3, B(0, 2) = 3.4;
  B(1, 0) = 4.5, B(1, 1) = 5.6, B(1, 2) = 6.7;
  B(2, 0) = 7.8, B(2, 1) = 8.9, B(2, 2) = 9.0;

  bool res = A.EqMatrix(B);
  bool res2 = B.EqMatrix(A);
  EXPECT_TRUE(res);
  EXPECT_TRUE(res2);
  EXPECT_TRUE(res = res2);
}

TEST(TestEq, EqMatrix4) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.2, m(0, 1) = 2.3;
  m(1, 0) = 4.5, m(1, 1) = 5.6;

  S21Matrix n(2, 2);
  n(0, 0) = 1.4, n(0, 1) = 5.3;
  n(1, 0) = 4.5, n(1, 1) = 1.6;

  bool res = m.EqMatrix(n);
  bool res2 = n.EqMatrix(m);
  EXPECT_FALSE(res);
  EXPECT_FALSE(res2);
  EXPECT_FALSE(res = res2);
}

TEST(TestSum, SumMatrix1) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.2, A(0, 1) = 2.3;
  A(1, 0) = 4.5, A(1, 1) = 5.6;

  S21Matrix B(3, 2);
  B(0, 0) = 1.2, B(0, 1) = 2.3;
  B(1, 0) = 4.5, B(1, 1) = 5.6;
  B(2, 0) = 7.8, B(2, 1) = 8.9;

  ASSERT_ANY_THROW(A.SumMatrix(B));
}

TEST(TestSum, SumMatrix2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 3, A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 3, B(1, 1) = 4;

  S21Matrix C(2, 2);
  C(0, 0) = 2, C(0, 1) = 4;
  C(1, 0) = 6, C(1, 1) = 8;

  A.SumMatrix(B);

  EXPECT_TRUE(A == C);
}

TEST(TestSum, SumMatrix3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1, matrix(0, 1) = 2, matrix(0, 2) = 3;
  matrix(1, 0) = 4, matrix(1, 1) = 5, matrix(1, 2) = 6;
  matrix(2, 0) = 7, matrix(2, 1) = 8, matrix(2, 2) = 9;

  S21Matrix B(3, 3);
  B(0, 0) = 1, B(0, 1) = 2, B(0, 2) = 3;
  B(1, 0) = 4, B(1, 1) = 5, B(1, 2) = 6;
  B(2, 0) = 7, B(2, 1) = 8, B(2, 2) = 9;

  S21Matrix C(3, 3);
  C(0, 0) = 2, C(0, 1) = 4, C(0, 2) = 6;
  C(1, 0) = 8, C(1, 1) = 10, C(1, 2) = 12;
  C(2, 0) = 14, C(2, 1) = 16, C(2, 2) = 18;

  matrix += B;

  EXPECT_TRUE(matrix == C);
}

TEST(TestSum, SumMatrix4) {
  S21Matrix matrix(2, 2);
  S21Matrix B(3, 3);

  EXPECT_THROW(matrix.SumMatrix(B), std::invalid_argument);
}

TEST(TestSub, SubMatrix1) {
  S21Matrix A(2, 2);
  A(0, 0) = 3, A(0, 1) = 5;
  A(1, 0) = 4, A(1, 1) = 6;

  S21Matrix B(2, 2);
  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 2, B(1, 1) = 4;

  S21Matrix C(2, 2);
  C(0, 0) = 2, C(0, 1) = 3;
  C(1, 0) = 2, C(1, 1) = 2;

  A.SubMatrix(B);

  EXPECT_TRUE(A == C);
}

TEST(TestSub, SubMatrix2) {
  S21Matrix m(4, 4);
  S21Matrix n(3, 3);

  EXPECT_THROW(m.SubMatrix(n), std::invalid_argument);
}

TEST(TestMulNumber, MulNumberMatrix1) {
  S21Matrix A(2, 2);
  A(0, 0) = 2, A(0, 1) = 4;
  A(1, 0) = 5, A(1, 1) = 6;

  const double num = 2;

  S21Matrix res(2, 2);
  res(0, 0) = 4, res(0, 1) = 8;
  res(1, 0) = 10, res(1, 1) = 12;

  A.MulNumber(num);
  EXPECT_TRUE(A == res);
}

TEST(TestMulNumber, MulNumberMatrix2) {
  S21Matrix arr(2, 2);
  arr(0, 0) = 1, arr(0, 1) = 1;
  arr(1, 0) = 1, arr(1, 1) = 1;

  const double number = 2.4;

  S21Matrix res(2, 2);
  res(0, 0) = 2.4, res(0, 1) = 2.4;
  res(1, 0) = 2.4, res(1, 1) = 2.4;

  arr.MulNumber(number);

  EXPECT_TRUE(arr == res);
}

TEST(TestMulMatrix, MulMatrix1) {
  S21Matrix W(3, 2);
  S21Matrix X(1, 1);

  EXPECT_THROW(W.MulMatrix(X), std::invalid_argument);
}

TEST(TestMulMatrix, MulMatrix2) {
  S21Matrix A(2, 2);
  A(0, 0) = 2, A(0, 1) = 3;
  A(1, 0) = 2, A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 2, B(1, 1) = 1;

  S21Matrix C(2, 2);
  C(0, 0) = 8, C(0, 1) = 7;
  C(1, 0) = 10, C(1, 1) = 8;

  A.MulMatrix(B);

  EXPECT_TRUE(A == C);
}

TEST(TestTransponse, TransponseMatrix1) {
  S21Matrix A(3, 2);

  A(0, 0) = 2.3, A(0, 1) = 1.5;
  A(1, 0) = 3.6, A(1, 1) = 2.7;
  A(2, 0) = 1.3, A(2, 1) = 2.4;

  S21Matrix res_matrix(2, 3);

  res_matrix(0, 0) = 2.3, res_matrix(0, 1) = 3.6, res_matrix(0, 2) = 1.3;
  res_matrix(1, 0) = 1.5, res_matrix(1, 1) = 2.7, res_matrix(1, 2) = 2.4;

  EXPECT_TRUE(A.Transponse() == res_matrix);
}

TEST(TestTransponse, TransponseMatrix2) {
  S21Matrix A(3, 3);

  A(0, 0) = 2, A(0, 1) = 1, A(0, 2) = 3;
  A(1, 0) = 4, A(1, 1) = 5, A(1, 2) = 6;
  A(2, 0) = 7, A(2, 1) = 8, A(2, 2) = 9;

  S21Matrix res_matrix(3, 3);

  res_matrix(0, 0) = 2, res_matrix(0, 1) = 4, res_matrix(0, 2) = 7;
  res_matrix(1, 0) = 1, res_matrix(1, 1) = 5, res_matrix(1, 2) = 8;
  res_matrix(2, 0) = 3, res_matrix(2, 1) = 6, res_matrix(2, 2) = 9;

  EXPECT_TRUE(A.Transponse() == res_matrix);
}

TEST(Test_determinant, Determinant_matrix) {
  S21Matrix A(3, 3);

  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 0, A(1, 1) = 4, A(1, 2) = 5;
  A(2, 0) = 1, A(2, 1) = 0, A(2, 2) = 6;

  double det = A.Determinant();

  EXPECT_TRUE(det = A.Determinant());
}

TEST(Test_determinant, Determinant_matrix2) {
  S21Matrix A(2, 3);

  EXPECT_THROW(A.Determinant(), std::invalid_argument);
}

TEST(Test_determinant, Determinant_matrix3) {
  S21Matrix A(3, 3);

  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 0, A(1, 1) = 4, A(1, 2) = 5;
  A(2, 0) = 1, A(2, 1) = 0, A(2, 2) = 6;

  double det = A.Determinant();

  EXPECT_TRUE(det = A.Determinant());

  EXPECT_DOUBLE_EQ(det, 22);
}

TEST(Test_calc_compl, Calc_complements_matrix) {
  S21Matrix A(3, 3);

  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 0, A(1, 1) = 4, A(1, 2) = 5;
  A(2, 0) = 1, A(2, 1) = 0, A(2, 2) = 6;

  S21Matrix calc = A.CalcComplements();

  EXPECT_TRUE(calc == A.CalcComplements());
}

TEST(Test_calc_compl, Calc_complements_matrix2) {
  S21Matrix A(3, 3);

  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 0, A(1, 1) = 4, A(1, 2) = 5;
  A(2, 0) = 1, A(2, 1) = 0, A(2, 2) = 6;

  S21Matrix calc = A.CalcComplements();

  EXPECT_TRUE(calc == A.CalcComplements());

  EXPECT_DOUBLE_EQ(calc(0, 0), 24);
  EXPECT_DOUBLE_EQ(calc(0, 1), 5);
  EXPECT_DOUBLE_EQ(calc(0, 2), -4);
  EXPECT_DOUBLE_EQ(calc(1, 0), -12);
  EXPECT_DOUBLE_EQ(calc(1, 1), 3);
  EXPECT_DOUBLE_EQ(calc(1, 2), 2);
  EXPECT_DOUBLE_EQ(calc(2, 0), -2);
  EXPECT_DOUBLE_EQ(calc(2, 1), -5);
  EXPECT_DOUBLE_EQ(calc(2, 2), 4);
}

TEST(Test_calc_compl, Calc_complements_matrix3) {
  S21Matrix A(3, 4);

  EXPECT_THROW(A.CalcComplements(), std::invalid_argument);
}

TEST(Test_inverse, Inverse_matrix1) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 1, matrix(0, 1) = 2, matrix(0, 2) = 3;
  matrix(1, 0) = 0, matrix(1, 1) = 1, matrix(1, 2) = 4;
  matrix(2, 0) = 5, matrix(2, 1) = 6, matrix(2, 2) = 0;

  S21Matrix inverse = matrix.InverseMatrix();

  EXPECT_TRUE(inverse == matrix.InverseMatrix());

  EXPECT_DOUBLE_EQ(inverse(0, 0), -24);
  EXPECT_DOUBLE_EQ(inverse(0, 1), 18);
  EXPECT_DOUBLE_EQ(inverse(0, 2), 5);
  EXPECT_DOUBLE_EQ(inverse(1, 0), 20);
  EXPECT_DOUBLE_EQ(inverse(1, 1), -15);
  EXPECT_DOUBLE_EQ(inverse(1, 2), -4);
  EXPECT_DOUBLE_EQ(inverse(2, 0), -5);
  EXPECT_DOUBLE_EQ(inverse(2, 1), 4);
  EXPECT_DOUBLE_EQ(inverse(2, 2), 1);
}

TEST(Test_inverse, Inverse_matrix2) {
  S21Matrix A(3, 3);

  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 2, A(1, 1) = 4, A(1, 2) = 6;
  A(2, 0) = 3, A(2, 1) = 6, A(2, 2) = 9;

  EXPECT_THROW(A.InverseMatrix(), std::invalid_argument);
}

TEST(Test_operator_plus, operator_plus) {
  S21Matrix A(3, 3);

  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 2, A(1, 1) = 4, A(1, 2) = 6;
  A(2, 0) = 3, A(2, 1) = 6, A(2, 2) = 3;

  S21Matrix B(3, 3);

  B(0, 0) = 1, B(0, 1) = 2, B(0, 2) = 3;
  B(1, 0) = 2, B(1, 1) = 4, B(1, 2) = 1;
  B(2, 0) = 3, B(2, 1) = 1, B(2, 2) = 2;

  S21Matrix C = A + B;

  EXPECT_TRUE(C == A + B);

  EXPECT_DOUBLE_EQ(C(0, 0), 2);
  EXPECT_DOUBLE_EQ(C(0, 1), 4);
  EXPECT_DOUBLE_EQ(C(0, 2), 6);
  EXPECT_DOUBLE_EQ(C(1, 0), 4);
  EXPECT_DOUBLE_EQ(C(1, 1), 8);
  EXPECT_DOUBLE_EQ(C(1, 2), 7);
  EXPECT_DOUBLE_EQ(C(2, 0), 6);
  EXPECT_DOUBLE_EQ(C(2, 1), 7);
  EXPECT_DOUBLE_EQ(C(2, 2), 5);

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(0, 2), 3);
  EXPECT_DOUBLE_EQ(A(1, 0), 2);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 2), 6);
  EXPECT_DOUBLE_EQ(A(2, 0), 3);
  EXPECT_DOUBLE_EQ(A(2, 1), 6);
  EXPECT_DOUBLE_EQ(A(2, 2), 3);
}

TEST(Test_operator_plus_assignment, operator_plus_assignment) {
  S21Matrix A(2, 2);

  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 3, A(1, 1) = 4;

  S21Matrix B(2, 2);

  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 3, B(1, 1) = 4;

  A += B;

  EXPECT_DOUBLE_EQ(A(0, 0), 2);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 6);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(0, 1), 2);
  EXPECT_DOUBLE_EQ(B(1, 0), 3);
  EXPECT_DOUBLE_EQ(B(1, 1), 4);
}

TEST(Test_operator_minus, operator_minus) {
  S21Matrix A(2, 2);

  A(0, 0) = 6, A(0, 1) = 8;
  A(1, 0) = 7, A(1, 1) = 5;

  S21Matrix B(2, 2);

  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 3, B(1, 1) = 4;

  S21Matrix C = A - B;

  EXPECT_TRUE(C == A - B);

  EXPECT_DOUBLE_EQ(C(0, 0), 5);
  EXPECT_DOUBLE_EQ(C(0, 1), 6);
  EXPECT_DOUBLE_EQ(C(1, 0), 4);
  EXPECT_DOUBLE_EQ(C(1, 1), 1);

  EXPECT_DOUBLE_EQ(A(0, 0), 6);
  EXPECT_DOUBLE_EQ(A(0, 1), 8);
  EXPECT_DOUBLE_EQ(A(1, 0), 7);
  EXPECT_DOUBLE_EQ(A(1, 1), 5);
}

TEST(Test_operator_minus_assignment, operator_minus_assignment) {
  S21Matrix A(2, 2);

  A(0, 0) = 6, A(0, 1) = 8;
  A(1, 0) = 7, A(1, 1) = 5;

  S21Matrix B(2, 2);

  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 3, B(1, 1) = 4;

  A -= B;

  EXPECT_DOUBLE_EQ(A(0, 0), 5);

  EXPECT_DOUBLE_EQ(A(0, 1), 6);
  EXPECT_DOUBLE_EQ(A(1, 0), 4);
  EXPECT_DOUBLE_EQ(A(1, 1), 1);

  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(0, 1), 2);
  EXPECT_DOUBLE_EQ(B(1, 0), 3);
  EXPECT_DOUBLE_EQ(B(1, 1), 4);
}

TEST(Test_operator_mul_num, operator_mul_num) {
  S21Matrix A(2, 2);

  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 3, A(1, 1) = 4;

  double num = 2;

  S21Matrix B = A * num;

  EXPECT_DOUBLE_EQ(B(0, 0), 2);
  EXPECT_DOUBLE_EQ(B(0, 1), 4);
  EXPECT_DOUBLE_EQ(B(1, 0), 6);
  EXPECT_DOUBLE_EQ(B(1, 1), 8);

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);
}

TEST(Test_operator_mul_num_assignment, operator_mul_num_assignment) {
  S21Matrix A(2, 2);

  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 3, A(1, 1) = 4;

  double num = 2;

  A *= num;

  EXPECT_DOUBLE_EQ(A(0, 0), 2);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 6);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  EXPECT_DOUBLE_EQ(num, 2);
}

TEST(Test_operator_mul_matrix, operator_mul_matrix) {
  S21Matrix A(2, 2);

  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 3, A(1, 1) = 4;

  S21Matrix B(2, 2);

  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 3, B(1, 1) = 4;

  S21Matrix C = A * B;

  EXPECT_TRUE(C == A * B);

  EXPECT_DOUBLE_EQ(C(0, 0), 7);
  EXPECT_DOUBLE_EQ(C(0, 1), 10);
  EXPECT_DOUBLE_EQ(C(1, 0), 15);
  EXPECT_DOUBLE_EQ(C(1, 1), 22);

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);
}

TEST(Test_operator_mul_matrix_assignment, operator_mul_matrix_assignment) {
  S21Matrix A(2, 2);

  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 3, A(1, 1) = 4;

  S21Matrix B(2, 2);

  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 3, B(1, 1) = 4;

  A *= B;

  EXPECT_DOUBLE_EQ(A(0, 0), 7);
  EXPECT_DOUBLE_EQ(A(0, 1), 10);
  EXPECT_DOUBLE_EQ(A(1, 0), 15);
  EXPECT_DOUBLE_EQ(A(1, 1), 22);
}

TEST(Test_operator_asign, operator_asign) {
  S21Matrix A(2, 2);

  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 3, A(1, 1) = 4;

  S21Matrix B(2, 2);

  B(0, 0) = 5, B(0, 1) = 6;
  B(1, 0) = 7, B(1, 1) = 8;

  A = B;

  EXPECT_DOUBLE_EQ(A(0, 0), 5);
  EXPECT_DOUBLE_EQ(A(0, 1), 6);
  EXPECT_DOUBLE_EQ(A(1, 0), 7);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  EXPECT_DOUBLE_EQ(B(0, 0), 5);
  EXPECT_DOUBLE_EQ(B(0, 1), 6);
  EXPECT_DOUBLE_EQ(B(1, 0), 7);
  EXPECT_DOUBLE_EQ(B(1, 1), 8);
}

TEST(Test_operator_eq, operator_eq) {
  S21Matrix A(2, 2);

  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 3, A(1, 1) = 4;

  S21Matrix B(2, 2);

  B(0, 0) = 1, B(0, 1) = 2;
  B(1, 0) = 3, B(1, 1) = 4;

  EXPECT_TRUE(A == B);
}

TEST(Test_access_element, access_element) {
  S21Matrix A(3, 3);

  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 4, A(1, 1) = 5, A(1, 2) = 6;
  A(2, 0) = 7, A(2, 1) = 8, A(2, 2) = 9;

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
}

TEST(Test_access_out_of_range, access_out_of_range2) {
  S21Matrix A(3, 3);

  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 4, A(1, 1) = 5, A(1, 2) = 6;
  A(2, 0) = 7, A(2, 1) = 8, A(2, 2) = 9;

  EXPECT_THROW(A(4, 4), std::out_of_range);
}
TEST(Test_operator_GetRows, operator_GetRows) {
  S21Matrix A(3, 4);

  int rows = A.GetRows();

  EXPECT_EQ(rows, 3);
}

TEST(Test_operator_GetCols, operator_GetCols) {
  S21Matrix B(4, 5);

  int cols = B.GetCols();

  EXPECT_EQ(cols, 5);
}

TEST(Test_operator_SetRows, operator_SetRows) {
  S21Matrix A(3, 3);

  A.SetRows(2);

  EXPECT_EQ(A.GetRows(), 2);
}

TEST(Test_operator_SetCols, operator_SetCols) {
  S21Matrix B(4, 4);

  B.SetCols(3);

  EXPECT_EQ(B.GetCols(), 3);
}

int main() {
  ::testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}