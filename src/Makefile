CC = gcc
CXX = g++
MINGW = /usr/i686-w64-mingw32
CC_WIN = i686-w64-mingw32-gcc
CXX_WIN = i686-w64-mingw32-g++
LIBS_WIN = -L$(MINGW)/lib/ -lmingw32  -mwindows -lole32 -lgdi32 -ldxguid -lddraw -limm32
TARGET = UA_source
OBJS =  \
	ade.cpp\
	area.cpp\
	amesh.cpp\
        bitmap.cpp\
	base.cpp\
	classes.cpp\
	display.cpp\
	embed.cpp\
	engine_gfx.cpp\
	engine_input.cpp\
	engine_miles.cpp\
	engine_tform.cpp\
	glob_funcs.cpp\
	ilbm.cpp\
	ini.cpp\
	log.cpp\
	main.cpp\
	MC.cpp\
	MFILE.cpp\
	nlist.cpp\
	nucleas.cpp\
	raster.cpp\
	rsrc.cpp\
	skeleton.cpp\
	sklt.cpp\
	utils.cpp\
	win3d.cpp\
	windd.cpp
	
WINOBJ = \
	win_funct.cpp

win32: $(OBJS)
	$(CXX_WIN) -Wno-write-strings -O3 -Os -o $(TARGET).exe $(OBJS) $(LIBS_WIN) -m32 -I $(MINGW)/include/

clean:
	rm -f $(TARGET) $(TARGET_DINGOO) *.o