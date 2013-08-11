#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

#include <cstdlib>

using namespace std;

#include "globals.hpp"

#include "sparseM.hpp"
#include "sparseM_parser.hpp"
#include "sparseM_math.hpp"
#include "sparseM_utilities.hpp"


int main(int argc, char* argv[])
{
  ifstream m_File("file_2.matrix");
  
  if(!m_File)
  {
    cout << "Unable to open file" << endl;
    exit(0);
  }
  
  SparseMatrix sMatrix;
  
  SparseMatrixParser sMatrixParser;
  sMatrixParser.read_HB_file(m_File,
			     sMatrix.numRow,
			     sMatrix.numCol,
			     sMatrix.numElement,
			     sMatrix.COLPTR,
			     sMatrix.ROWIND,
			     sMatrix.VALUES);
  
  cout << "Number of Rows : " << sMatrix.numRow << endl;
  cout << "Number of Cols : " << sMatrix.numCol << endl;
  cout << "Number of Elements : " << sMatrix.numElement << endl;
  
  //cout << sMatrix.COLPTR[0] << endl;
  
  sMatrix.display();

  
  for(int i=0; i<=sMatrix.numCol; i++)
  {
    cout << sMatrix.COLPTR[i] << ", "; 
  }
  cout << endl;
  

  for(int i=0; i<sMatrix.numElement; i++)
  {
    cout << sMatrix.ROWIND[i] << ", ";
  }
  
  cout << endl;
  
  double y[] = {1,1,1,1};
  double z[] = {0,0,0,0};
  
  //SparseM_Math::daxpy(sMatrix, y, z);
  
  double D[] = {4.5, 0, 3.2, 0, 3.1, 2.9, 0, 0.9, 0, 1.7, 3.0, 0, 3.5, .4, 0, 1.0};
  
  
  SparseMatrix sm;
  SparseM_Utils::denseToSparse(sm, D, 4, 4);
  sm.display();
  for(int i=0; i<sm.numElement; i++) cout << sm.ROWIND[i] << ", ";
  cout << endl;
  for(int i=0; i<=sm.numCol; i++) cout << sm.COLPTR[i] << ", ";
  cout << endl;
  /*
  for(int i=0; i<4; i++)
  {
    cout << z[i] << endl;
  }*/
  
  return 0;
}