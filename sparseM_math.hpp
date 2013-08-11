class SparseMatrix;

class SparseM_Math
{
public:
  static void daxpy(const SparseMatrix& A, const double* x, double* y);  // y <- Ax + y
  static void multiply(const SparseMatrix& A, const SparseMatrix& B, const SparseMatrix& C); // C = A*B
};

void SparseM_Math::daxpy(const SparseMatrix& A, const double* x, double* y)
{
  for(int i=0; i<A.numCol; i++)
  {
    for(int j=A.COLPTR[i]; j<A.COLPTR[i+1]; j++) 
    {
      y[A.ROWIND[j]] += A.VALUES[j]*x[i];
    }
  }
}

void SparseM_Math::multiply(const SparseMatrix& A, const SparseMatrix& B, const SparseMatrix& C)
{
  
}