SUBDIRS = . check

lib_LTLIBRARIES = libfmatvec.la
libfmatvec_la_SOURCES = linear_algebra_double.cc \
			linear_algebra_complex.cc \
			atom.cc \
			_memory.cc \
			wrapper.cc \
			stream.cc \
			ast.cc

libfmatvec_la_CPPFLAGS = -I$(top_srcdir) -Dfmatvec_EXPORTS=1
fmatvecincludedir=$(includedir)/fmatvec
fmatvecinclude_HEADERS = diagonal_matrix.h \
			 atom.h \
			 toString.h \
			 fmatvec.h \
			 general_matrix.h \
			 linear_algebra_double.h \
			 linear_algebra_complex.h \
			 linear_algebra.h \
			 matrix.h \
			 _memory.h \
			 row_vector.h \
			 square_matrix.h \
			 symmetric_matrix.h \
			 types.h \
			 stream.h \
			 stream_impl.h \
			 vector.h \
			 band_matrix.h\
			 sparse_matrix.h\
			 range.h\
			 fixed_general_matrix.h\
			 fixed_square_matrix.h\
			 fixed_symmetric_matrix.h\
			 fixed_vector.h\
			 fixed_row_vector.h\
			 var_general_matrix.h\
			 var_square_matrix.h\
			 var_symmetric_matrix.h\
			 var_vector.h\
			 var_row_vector.h\
			 fixed_var_general_matrix.h\
			 var_fixed_general_matrix.h\
			 wrapper.h\
			 ast.h\
			 symbolic.h\
			 function.h\
			 symbolic_function.h\
			 symbolic_function1_temp.h\
			 symbolic_function2_temp.h
