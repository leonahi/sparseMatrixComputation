class SparseMatrix;


class SparseM_Utils
{
public:
  static void denseToSparse(SparseMatrix& A, const double* D, const uint numRows, const uint numCols);
  
};

void SparseM_Utils::denseToSparse(SparseMatrix& A, const double* D, const uint numRows, const uint numCols)
{
  A.numRow = numRows;
  A.numCol = numCols;
  A.COLPTR = new uint[numCols+1];
  A.COLPTR[0] = 0;
  
  list<double> values;
  list<uint> rowIndex;
  uint colPtr = 0;
  
  for(uint i=0; i<numCols; i++)
  {
    A.COLPTR[i] = colPtr;
    for(uint j=0; j<numRows; j++)
    {
      if(D[j*numCols + i])
      {
        values.push_back(D[j*numCols + i]);
        rowIndex.push_back(j);
        ++colPtr;
      }
    }
  }
  A.COLPTR[numCols] = values.size();
  
  A.ROWIND = new uint[rowIndex.size()];
  A.VALUES = new double[values.size()];
  A.numElement = values.size();
  
  for(int i=0; !values.empty(); i++)
  {
    A.ROWIND[i] = rowIndex.front();
    A.VALUES[i] = values.front();
    rowIndex.pop_front();
    values.pop_front();
  }
}