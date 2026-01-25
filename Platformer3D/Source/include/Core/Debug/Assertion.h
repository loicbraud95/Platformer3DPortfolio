#pragma once

#ifdef NDEBUG
#define Assert(x) if(x == false){abort();}
#else
#define Assert(x) if(x == false){__debugbreak();}
#endif
