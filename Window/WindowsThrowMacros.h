#pragma once


#define CHWND_EXCEPT(hr) WS_Windows::WindowException(_LINE_,_FILE_,(hr))
//#define CHWND_LAST_EXCEPT() WS_WS_Windows::WindowException