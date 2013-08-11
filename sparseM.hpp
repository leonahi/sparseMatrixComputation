class SparseMatrix  
 {  
 public:  
  unsigned int numRow;    // Number of rows  
  unsigned int numCol;    // Number of columns  
  unsigned int numElement;  // Number non zero elements of the sparse matrix   
  unsigned int* ROWIND;    // Row index of the matrix (Size = numElement)  
  unsigned int* COLPTR;    // Column pointer of the matrix (Size = numCol+1)  
  double* VALUES;       // Non zero elements in the sparse matrix (Size = numElement)  
  SparseMatrix();  
  ~SparseMatrix();
  void display();
  
 };  
 inline SparseMatrix::SparseMatrix() : numRow(0), numCol(0), numElement(0)  
 {  
  ROWIND = NULL;  
  COLPTR = NULL;  
  VALUES = NULL;  
 }  
 inline SparseMatrix::~SparseMatrix()  
 {  
  delete [] ROWIND;  
  delete [] COLPTR;  
  delete [] VALUES;  
 }  

 inline void SparseMatrix::display()
 {
   cout << "Column wise element list : ";
   for(int i=0; i<numElement; i++)
   {
     cout << VALUES[i] << ", ";
   }
   cout << endl;
 }