#pragma once

#ifdef DG_EXPORTS
#define DG_API __declspec(dllexport)
#else
#define DG_API __declspec(dllimport)
#endif
