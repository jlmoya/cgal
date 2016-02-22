// Copyright (c) 2005  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CG-LAB; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CG-LAB.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Id: cgal_exception.cpp 6 2005-12-05 15:53:46Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/cgal_exception.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include "cgal_exception.h"

cgal_exception::cgal_exception(const std::string what,const std::string expr,const std::string file,int line,
								const std::string msg ):my_what(what),my_expr(expr),my_file(file),my_line(line),my_msg(msg){};


// static void cgal_error_handler(const char* what,const char* expr,const char* file,int line,const char* msg )
// {
//     std::cerr << "CGAL error: " << what << " violation!" << std::endl
//          << "Expr: " << expr << std::endl
//          << "File: " << file << std::endl
//          << "Line: " << line << std::endl;
//     if ( msg != 0)
//         std::cerr << "Explanation:" << msg << std::endl;
//
// 		throw cgal_exception(what,expr,file,line,msg);
// }
//
