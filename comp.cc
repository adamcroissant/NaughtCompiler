/* main.cc */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include "StrUtil.h"

#include "yy.h"

#include "AST_node.h"
#include "IntLiteral_node.h"

StrUtil *AST = nullptr;

int _WANT_DEBUG = 0;

#define YY_NO_UNPUT

using namespace std;

  // We allow either a single filename, or the two token combination "- filename".
  // For the former, we read source from the named file.
  // For the latter, we read from stdin, but write an output file with name
  // based on the one given on the command line.

void usage(const char* exeName) {
    cerr << "Usage: " << exeName << " [-d] [-o outfilename] infilename" << endl
         << "   -d enables debug printing." << endl
         << "   If the filename is '-', read from stdin." << endl
         << "   The infilename must end with '.n'." << endl;
    exit( EXIT_FAILURE );
}

int main(int argc, char **argv)
{ string inFilename;
  string outFilename;
  int opt;
  while ((opt = getopt(argc, argv, "do:v")) != -1) {
    switch(opt) {
      case 'd': _WANT_DEBUG = 1;
                break;
      case 'o': outFilename = optarg;
                break;
      case 'v': cout << "Version 0.9.0" << endl;
                return EXIT_SUCCESS;
      default: usage(argv[0]);
    }
  }

  if ( argc - optind != 1 ) usage(argv[0]);

  inFilename = argv[optind];
  if ( inFilename.compare("-") != 0 ) {
    // Verify that file name ends with ".n" and create output file name.
    int len = inFilename.length();
    if ( len < 3 || inFilename[len-2]!='.' || inFilename[len-1]!='n') usage(argv[0]);
    if (freopen(argv[optind], "r", stdin) == NULL) {
      cerr << argv[0] << ": File " << argv[1] << " cannot be opened.\n";
      return EXIT_FAILURE;
    }
  }
  
  if ( outFilename.empty() ) { 
    outFilename = inFilename;
    outFilename[outFilename.length()-1] = 'c';
  }

  // The parser leaves the AST in variable AST
  if ( yyparse() ) return EXIT_FAILURE;

  if ( AST == nullptr ) return EXIT_SUCCESS;  // empty file?
  
  // Generate code
  // ...

  // clean up
  delete AST;

  return EXIT_SUCCESS;
}

