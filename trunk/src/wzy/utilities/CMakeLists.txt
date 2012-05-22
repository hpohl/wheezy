add_library(wzyutilities SHARED
exception.cpp exception.hpp
general.cpp general.hpp

helpers/assign.hpp
helpers/operations.hpp

mat.cpp mat.hpp
mat/info.hpp
mat/matdef.hpp
mat/matfwd.hpp
mat/functions/general.hpp
mat/functions/math.hpp
mat/operators/math.hpp

vec.cpp vec.hpp
vec/aliases.hpp
vec/impl.hpp
vec/info.hpp
vec/vecdef.hpp
vec/vecfwd.hpp
vec/functions/math.hpp
vec/functions/general.hpp
vec/operators/logic.hpp
vec/operators/math.hpp

info.hpp
noncopyable.hpp
singleton.hpp
tmp.hpp
)
