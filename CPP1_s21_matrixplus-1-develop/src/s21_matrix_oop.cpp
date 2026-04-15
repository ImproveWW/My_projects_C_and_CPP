#include "s21_matrix_oop.h"

void S21Matrix::create_matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Invalid matrix size");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_];

  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];

    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}

void S21Matrix::copy_matrix(const S21Matrix& other) {
  create_matrix(other.rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::remove_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }

    delete[] matrix_;

    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) { create_matrix(rows, cols); }

S21Matrix::S21Matrix(const S21Matrix& other) { copy_matrix(other); }

S21Matrix::~S21Matrix() { remove_matrix(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          res = false;
        }
      }
    }
  }

  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    throw std::invalid_argument("Different sizes of matrices");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    throw std::invalid_argument("Different sizes of matrices");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Different sizes of matrices");
  }

  S21Matrix res(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      res.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = res;
}

S21Matrix S21Matrix::Transponse() const {
  S21Matrix res(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }

  return res;
}

S21Matrix S21Matrix::get_minor(int row, int coln) const {
  if (row < 0 || row >= rows_ || coln < 0 || coln >= cols_) {
    throw std::out_of_range("Row or column index is out of range");
  }

  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != coln) {
        minor.matrix_[i < row ? i : i - 1][j < coln ? j : j - 1] =
            matrix_[i][j];
      }
    }
  }
  return minor;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  double res = 0.0;

  if (rows_ == 1) {
    res = matrix_[0][0];
  } else {
    double temp = 0.0;
    double sign = 1.0;
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = get_minor(0, j);
      double minor_det = minor.Determinant();

      temp = matrix_[0][j] * minor_det;
      res += sign * temp;
      sign *= -1.0;
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  S21Matrix res(rows_, cols_);

  if (cols_ == 1) {
    res.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        res.matrix_[i][j] = pow(-1, i + j) * get_minor(i, j).Determinant();
      }
    }
  }

  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double deter = Determinant();

  if (fabs(deter) < 1e-7) {
    throw std::invalid_argument(
        "Determinant is zero, matrix is not invertible");
  }

  S21Matrix res(cols_, cols_);
  if (cols_ == 1) {
    res.matrix_[0][0] = 1.0 / deter;
  } else {
    res = CalcComplements().Transponse();
    res.MulNumber(1.0 / deter);
  }

  return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);

  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);

  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);

  return res;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res(*this);
  res.MulNumber(num);

  return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  remove_matrix();
  copy_matrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);

  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);

  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[i][j];
}
void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("Invalid number of rows");
  }

  S21Matrix temp(rows, cols_);

  int temp_rows = std::min(rows, rows_);

  for (int i = 0; i < temp_rows; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp;
}

int S21Matrix::GetRows() const { return rows_; }

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument("Invalid number of columns");
  }

  S21Matrix temp(rows_, cols);

  int temp_cols = std::min(cols, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < temp_cols; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp;
}

int S21Matrix::GetCols() const { return cols_; }