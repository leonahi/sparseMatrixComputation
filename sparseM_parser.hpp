class SparseMatrixParser  
 {  
 private:  
 //--------------Line 1-------------------------   
  string title;         // TITLE  
  string key;          // KEY  
 //--------------Line 2-------------------------   
  unsigned int totcrd;     // TOTCRD - Total Number of data lines.  
  unsigned int ptrcrd;     // PTRCRD - Number of data lines for pointer.  
  unsigned int indcrd;     // INDCRD - Number of data lines for row or variable indices.  
  unsigned int valcrd;     // VALCRD - Number of data lines for numercal values of matrix entries.  
  unsigned int rhscrd;     // RHSCRD - Number of data lines for right hand side vectors, starting guesses, and solutions.  
 //--------------Line 3-------------------------   
  string mxtype;        // MXTYPE - Matrix type.  
  unsigned int nrow;      // NROW  - Number of rows or variables.  
  unsigned int ncol;      // NCOL  - Number of columns or elements.  
  unsigned int nnzero;     // NNZERO - Number of row or variable indices.  
  unsigned int neltvl;     // NELTVL - Number of elemental matrix entries.  
 //--------------Line 4-------------------------   
  string ptrfmt;        // PTRFMT - FORTRAN I/O format for pointers  
  string indfmt;        // INDFMT - FORTRAN I/O format for row or variable indices  
  string valfmt;        // VALFMT - FORTRAN I/O format for matrix entries  
  string rhsfmt;        // RHSFMT - FORTRAN I/O format for right hand sides, initial guesses, and solutions  
 //--------------Line 5-------------------------   
  string rhstyp;        // RHSTYP - Describes the right hand side information  
  unsigned int nrhs;      // NRHS  - Integer, the number of right hand sides  
  unsigned int nrhsix;     // NRHSIX - Integer, number of row indices  
  void error(ifstream& file)  
  {  
   if(file.eof())  
   {  
    cout<<"Fatal error : Input file format is not correct"<<endl;  
    exit(1);  
   }  
  }  
  void checkMatrixType(string& mxtype);  
  
 public:  
  SparseMatrixParser() : totcrd(0), ptrcrd(0), indcrd(0), valcrd(0), rhscrd(0), nrow(0), ncol(0), nnzero(0), neltvl(0)  
  {}  
  void read_HB_file(ifstream& file, unsigned int& numRow, unsigned int& numCol, unsigned int& numElement, unsigned int*& COLPTR, unsigned int*& ROWIND, double*& VALUES);  
 };  
 
 void SparseMatrixParser::read_HB_file(ifstream& file, unsigned int& numRow, unsigned int& numCol, unsigned int& numElement, unsigned int*& COLPTR, unsigned int*& ROWIND, double*& VALUES)  
 {  
  stringstream SS;  
  string LINE;  
  LINE.reserve(80);  
 //------------------Reading first line-------------------  
  title.reserve(72);  
  key.reserve(8);  
  getline(file, LINE);  
  error(file);  
  title = LINE.substr(0,71);  
  key = LINE.substr(72,79);  
 //------------------Reading second line------------------  
  getline(file, LINE);  
  error(file);  
  SS.clear();  
  SS.str("");  
  SS.str(LINE);  
  SS >> totcrd >> ptrcrd >> indcrd >> valcrd >> rhscrd;  
 //------------------Reading third line--------------------   
  mxtype.reserve(3);  
  getline(file, LINE);  
  error(file);  
  SS.clear();  
  SS.str("");  
  SS.str(LINE);  
  SS >> mxtype >> nrow >> ncol >> nnzero >> neltvl;  
 //------------------Reading fourth line--------------------  
  ptrfmt.reserve(16);   
  indfmt.reserve(16);   
  valfmt.reserve(20);   
  rhsfmt.reserve(20);  
  getline(file, LINE);  
  error(file);  
  SS.clear();  
  SS.str("");  
  SS.str(LINE);  
  SS >> ptrfmt >> indfmt >> valfmt >> rhsfmt;   
 //-------------------Reading fifth line (only if 0 < rhscrd!)---------------------  
 rhstyp.reserve(3);  
 if(rhscrd > 0)  
 {  
  getline(file, LINE);  
  error(file);  
  SS.clear();  
  SS.str("");  
  SS.str(LINE);  
  SS >> rhstyp >> nrhs >> nrhsix;  
  cout<<"Sorry! this code only reads HB sparse matrix file format with no right hand side"<<endl;  
  exit(1);  
 }  
 checkMatrixType(mxtype);              // Check type of matrix (This code only reads real, assembled matrix)  
 numRow = nrow;  
 numCol = ncol;  
 numElement = nnzero;  
 COLPTR = new unsigned int[ncol+1]();  
 ROWIND = new unsigned int[nnzero]();   
 VALUES = new double[nnzero]();  
 unsigned int temp_ui;  
 unsigned int k=0;  
 for(int i=0; i<ptrcrd; i++)            // Storing Column pointer  
 {  
  getline(file, LINE);  
  SS.clear();  
  SS.str("");  
  SS.str(LINE);  
  while(SS.good())  
  {  
   SS >> temp_ui;  
   COLPTR[k] = temp_ui;  
   k++;  
   if(k==ncol+1) break;  
  }  
 }  
 k=0;  
 for(int i=0; i<indcrd; i++)            // Sroring Row index   
 {  
  getline(file, LINE);  
  SS.clear();  
  SS.str("");  
  SS.str(LINE);  
  while(SS.good())  
  {  
   SS >> temp_ui;  
   ROWIND[k] = temp_ui;  
   k++;  
   if(k==nnzero) break;  
  }  
 }  
 double temp_d;  
 k=0;  
 for(int i=0; i<valcrd; i++)             // Storing Non zero entries  
 {  
  getline(file, LINE);  
  SS.clear();  
  SS.str("");  
  SS.str(LINE);  
  while(SS.good())  
  {  
   SS >> temp_d;  
   VALUES[k] = temp_d;  
   k++;  
   if(k==nnzero) break;  
  }  
 }  
 LINE.clear();  
 }  
 
 inline void SparseMatrixParser::checkMatrixType(string& mxtype)  
 {  
  if(mxtype[0]!='R')  
  {  
   cout<<"Sorry! This code reads only real valued matrices"<<endl;  
   exit(1);  
  }  
  if(mxtype[2]!='A')  
  {  
   cout<<"Sorry! This code only reads assembled matrices"<<endl;  
   exit(1);  
  }  
 }  
