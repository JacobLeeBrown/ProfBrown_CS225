EXE_OS = testStackQueue
EXE_FILLS = testFills

OBJS_DIR = .objs

OBJS_FILLS_STUDENT = testFills.o solidColorPicker.o gradientColorPicker.o rainbowColorPicker.o
OBJS_FILLS_PROVIDED = animation.o rgbapixel.o png.o gridColorPicker.o
OBJS_OS_STUDENT = testStackQueue.o
OBJS_OS_PROVIDED = 

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: mp4.1 mp4.2
mp4.1: $(EXE_OS) $(EXE_OS)-asan
mp4.2: $(EXE_FILLS) $(EXE_FILLS)-asan

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE_OS):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_FILLS):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE_OS):         $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_OS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_OS_PROVIDED))
$(EXE_OS)-asan:    $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_OS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_OS_PROVIDED))
$(EXE_FILLS):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_FILLS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FILLS_PROVIDED))
$(EXE_FILLS)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_FILLS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FILLS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE_OS) $(EXE_OS)-asan $(EXE_FILLS) $(EXE_FILLS)-asan $(OBJS_DIR)

tidy: clean
	rm -rf images frames doc testStackQueue.out testFills.out

mydiffPM:
	diff frames/antiPacManBFS00.png soln_frames/antiPacManBFS00.png
	diff frames/antiPacManBFS01.png soln_frames/antiPacManBFS01.png
	diff frames/antiPacManBFS02.png soln_frames/antiPacManBFS02.png
	diff frames/antiPacManBFS03.png soln_frames/antiPacManBFS03.png
	diff frames/antiPacManBFS04.png soln_frames/antiPacManBFS04.png
	diff frames/antiPacManBFS05.png soln_frames/antiPacManBFS05.png
	diff frames/antiPacManBFS06.png soln_frames/antiPacManBFS06.png
	diff frames/antiPacManBFS07.png soln_frames/antiPacManBFS07.png
	diff frames/antiPacManBFS08.png soln_frames/antiPacManBFS08.png
	diff frames/antiPacManBFS09.png soln_frames/antiPacManBFS09.png
	diff frames/antiPacManBFS10.png soln_frames/antiPacManBFS10.png
	diff frames/antiPacManBFS11.png soln_frames/antiPacManBFS11.png
	diff frames/antiPacManBFS12.png soln_frames/antiPacManBFS12.png

	diff frames/antiPacManDFS00.png soln_frames/antiPacManDFS00.png
	diff frames/antiPacManDFS01.png soln_frames/antiPacManDFS01.png
	diff frames/antiPacManDFS02.png soln_frames/antiPacManDFS02.png
	diff frames/antiPacManDFS03.png soln_frames/antiPacManDFS03.png
	diff frames/antiPacManDFS04.png soln_frames/antiPacManDFS04.png
	diff frames/antiPacManDFS05.png soln_frames/antiPacManDFS05.png
	diff frames/antiPacManDFS06.png soln_frames/antiPacManDFS06.png
	diff frames/antiPacManDFS07.png soln_frames/antiPacManDFS07.png
	diff frames/antiPacManDFS08.png soln_frames/antiPacManDFS08.png
	diff frames/antiPacManDFS09.png soln_frames/antiPacManDFS09.png
	diff frames/antiPacManDFS10.png soln_frames/antiPacManDFS10.png
	diff frames/antiPacManDFS11.png soln_frames/antiPacManDFS11.png
	diff frames/antiPacManDFS12.png soln_frames/antiPacManDFS12.png

mydiffDFSFills:
	diff frames/dfsGradientTest0.png soln_frames/dfsGradientTest0.png
	diff frames/dfsGradientTest1.png soln_frames/dfsGradientTest1.png
	diff frames/dfsGradientTest2.png soln_frames/dfsGradientTest2.png
	diff frames/dfsGradientTest3.png soln_frames/dfsGradientTest3.png
	diff frames/dfsGradientTest4.png soln_frames/dfsGradientTest4.png
	diff frames/dfsGradientTest5.png soln_frames/dfsGradientTest5.png

	diff frames/dfsGridTest00.png soln_frames/dfsGridTest00.png
	diff frames/dfsGridTest01.png soln_frames/dfsGridTest01.png
	diff frames/dfsGridTest02.png soln_frames/dfsGridTest02.png
	diff frames/dfsGridTest03.png soln_frames/dfsGridTest03.png
	diff frames/dfsGridTest04.png soln_frames/dfsGridTest04.png
	diff frames/dfsGridTest05.png soln_frames/dfsGridTest05.png
	diff frames/dfsGridTest06.png soln_frames/dfsGridTest06.png
	diff frames/dfsGridTest07.png soln_frames/dfsGridTest07.png
	diff frames/dfsGridTest08.png soln_frames/dfsGridTest08.png
	diff frames/dfsGridTest09.png soln_frames/dfsGridTest09.png
	diff frames/dfsGridTest10.png soln_frames/dfsGridTest10.png
	diff frames/dfsGridTest11.png soln_frames/dfsGridTest11.png
	diff frames/dfsGridTest12.png soln_frames/dfsGridTest12.png
	diff frames/dfsGridTest13.png soln_frames/dfsGridTest13.png
	diff frames/dfsGridTest14.png soln_frames/dfsGridTest14.png
	diff frames/dfsGridTest15.png soln_frames/dfsGridTest15.png
	diff frames/dfsGridTest16.png soln_frames/dfsGridTest16.png

	diff frames/dfsSolidTest00.png soln_frames/dfsSolidTest00.png
	diff frames/dfsSolidTest01.png soln_frames/dfsSolidTest01.png
	diff frames/dfsSolidTest02.png soln_frames/dfsSolidTest02.png
	diff frames/dfsSolidTest03.png soln_frames/dfsSolidTest03.png
	diff frames/dfsSolidTest04.png soln_frames/dfsSolidTest04.png
	diff frames/dfsSolidTest05.png soln_frames/dfsSolidTest05.png
	diff frames/dfsSolidTest06.png soln_frames/dfsSolidTest06.png
	diff frames/dfsSolidTest07.png soln_frames/dfsSolidTest07.png
	diff frames/dfsSolidTest08.png soln_frames/dfsSolidTest08.png
	diff frames/dfsSolidTest09.png soln_frames/dfsSolidTest09.png
	diff frames/dfsSolidTest10.png soln_frames/dfsSolidTest10.png
	diff frames/dfsSolidTest11.png soln_frames/dfsSolidTest11.png
	diff frames/dfsSolidTest12.png soln_frames/dfsSolidTest12.png
	diff frames/dfsSolidTest13.png soln_frames/dfsSolidTest13.png
	diff frames/dfsSolidTest14.png soln_frames/dfsSolidTest14.png
	diff frames/dfsSolidTest15.png soln_frames/dfsSolidTest15.png
	diff frames/dfsSolidTest16.png soln_frames/dfsSolidTest16.png
	diff frames/dfsSolidTest17.png soln_frames/dfsSolidTest17.png
	diff frames/dfsSolidTest18.png soln_frames/dfsSolidTest18.png
	diff frames/dfsSolidTest19.png soln_frames/dfsSolidTest19.png
	diff frames/dfsSolidTest20.png soln_frames/dfsSolidTest20.png
	diff frames/dfsSolidTest21.png soln_frames/dfsSolidTest21.png
	diff frames/dfsSolidTest22.png soln_frames/dfsSolidTest22.png
	diff frames/dfsSolidTest23.png soln_frames/dfsSolidTest23.png
	diff frames/dfsSolidTest24.png soln_frames/dfsSolidTest24.png
	diff frames/dfsSolidTest25.png soln_frames/dfsSolidTest25.png
	diff frames/dfsSolidTest26.png soln_frames/dfsSolidTest26.png
	diff frames/dfsSolidTest27.png soln_frames/dfsSolidTest27.png
	diff frames/dfsSolidTest28.png soln_frames/dfsSolidTest28.png
	diff frames/dfsSolidTest29.png soln_frames/dfsSolidTest29.png
	diff frames/dfsSolidTest30.png soln_frames/dfsSolidTest30.png
	diff frames/dfsSolidTest31.png soln_frames/dfsSolidTest31.png
	diff frames/dfsSolidTest32.png soln_frames/dfsSolidTest32.png
	diff frames/dfsSolidTest33.png soln_frames/dfsSolidTest33.png
	diff frames/dfsSolidTest34.png soln_frames/dfsSolidTest34.png
	diff frames/dfsSolidTest35.png soln_frames/dfsSolidTest35.png
	diff frames/dfsSolidTest36.png soln_frames/dfsSolidTest36.png

mydiffBFSFills:
	diff frames/bfsGradientTest0.png soln_frames/bfsGradientTest0.png
	diff frames/bfsGradientTest1.png soln_frames/bfsGradientTest1.png
	diff frames/bfsGradientTest2.png soln_frames/bfsGradientTest2.png
	diff frames/bfsGradientTest3.png soln_frames/bfsGradientTest3.png
	diff frames/bfsGradientTest4.png soln_frames/bfsGradientTest4.png
	diff frames/bfsGradientTest5.png soln_frames/bfsGradientTest5.png

	diff frames/bfsGridTest00.png soln_frames/bfsGridTest00.png
	diff frames/bfsGridTest01.png soln_frames/bfsGridTest01.png
	diff frames/bfsGridTest02.png soln_frames/bfsGridTest02.png
	diff frames/bfsGridTest03.png soln_frames/bfsGridTest03.png
	diff frames/bfsGridTest04.png soln_frames/bfsGridTest04.png
	diff frames/bfsGridTest05.png soln_frames/bfsGridTest05.png
	diff frames/bfsGridTest06.png soln_frames/bfsGridTest06.png
	diff frames/bfsGridTest07.png soln_frames/bfsGridTest07.png
	diff frames/bfsGridTest08.png soln_frames/bfsGridTest08.png
	diff frames/bfsGridTest09.png soln_frames/bfsGridTest09.png
	diff frames/bfsGridTest10.png soln_frames/bfsGridTest10.png
	diff frames/bfsGridTest11.png soln_frames/bfsGridTest11.png
	diff frames/bfsGridTest12.png soln_frames/bfsGridTest12.png
	diff frames/bfsGridTest13.png soln_frames/bfsGridTest13.png
	diff frames/bfsGridTest14.png soln_frames/bfsGridTest14.png
	diff frames/bfsGridTest15.png soln_frames/bfsGridTest15.png
	diff frames/bfsGridTest16.png soln_frames/bfsGridTest16.png

	diff frames/bfsSolidTest00.png soln_frames/bfsSolidTest00.png
	diff frames/bfsSolidTest01.png soln_frames/bfsSolidTest01.png
	diff frames/bfsSolidTest02.png soln_frames/bfsSolidTest02.png
	diff frames/bfsSolidTest03.png soln_frames/bfsSolidTest03.png
	diff frames/bfsSolidTest04.png soln_frames/bfsSolidTest04.png
	diff frames/bfsSolidTest05.png soln_frames/bfsSolidTest05.png
	diff frames/bfsSolidTest06.png soln_frames/bfsSolidTest06.png
	diff frames/bfsSolidTest07.png soln_frames/bfsSolidTest07.png
	diff frames/bfsSolidTest08.png soln_frames/bfsSolidTest08.png
	diff frames/bfsSolidTest09.png soln_frames/bfsSolidTest09.png
	diff frames/bfsSolidTest10.png soln_frames/bfsSolidTest10.png
	diff frames/bfsSolidTest11.png soln_frames/bfsSolidTest11.png
	diff frames/bfsSolidTest12.png soln_frames/bfsSolidTest12.png
	diff frames/bfsSolidTest13.png soln_frames/bfsSolidTest13.png
	diff frames/bfsSolidTest14.png soln_frames/bfsSolidTest14.png
	diff frames/bfsSolidTest15.png soln_frames/bfsSolidTest15.png
	diff frames/bfsSolidTest16.png soln_frames/bfsSolidTest16.png
	diff frames/bfsSolidTest17.png soln_frames/bfsSolidTest17.png
	diff frames/bfsSolidTest18.png soln_frames/bfsSolidTest18.png
	diff frames/bfsSolidTest19.png soln_frames/bfsSolidTest19.png
	diff frames/bfsSolidTest20.png soln_frames/bfsSolidTest20.png
	diff frames/bfsSolidTest21.png soln_frames/bfsSolidTest21.png
	diff frames/bfsSolidTest22.png soln_frames/bfsSolidTest22.png
	diff frames/bfsSolidTest23.png soln_frames/bfsSolidTest23.png
	diff frames/bfsSolidTest24.png soln_frames/bfsSolidTest24.png
	diff frames/bfsSolidTest25.png soln_frames/bfsSolidTest25.png
	diff frames/bfsSolidTest26.png soln_frames/bfsSolidTest26.png
	diff frames/bfsSolidTest27.png soln_frames/bfsSolidTest27.png
	diff frames/bfsSolidTest28.png soln_frames/bfsSolidTest28.png
	diff frames/bfsSolidTest29.png soln_frames/bfsSolidTest29.png
	diff frames/bfsSolidTest30.png soln_frames/bfsSolidTest30.png
	diff frames/bfsSolidTest31.png soln_frames/bfsSolidTest31.png
	diff frames/bfsSolidTest32.png soln_frames/bfsSolidTest32.png
	diff frames/bfsSolidTest33.png soln_frames/bfsSolidTest33.png
	diff frames/bfsSolidTest34.png soln_frames/bfsSolidTest34.png
	diff frames/bfsSolidTest35.png soln_frames/bfsSolidTest35.png
	diff frames/bfsSolidTest36.png soln_frames/bfsSolidTest36.png

mydiffFrames: mydiffPM mydiffDFSFills mydiffBFSFills

mydiffImages:
	diff images/antiPacManBFS.gif soln_images/antiPacManBFS.gif
	diff images/antiPacManDFS.gif soln_images/antiPacManDFS.gif
	diff images/bfsGradientTest.gif soln_images/bfsGradientTest.gif
	diff images/dfsGradientTest.gif soln_images/dfsGradientTest.gif
	diff images/bfsGridTest.gif soln_images/bfsGridTest.gif
	diff images/dfsGridTest.gif soln_images/dfsGridTest.gif
	diff images/bfsSolidTest.gif soln_images/bfsSolidTest.gif
	diff images/dfsSolidTest.gif soln_images/dfsSolidTest.gif

	diff images/gradientColorPickerTest.png soln_images/gradientColorPickerTest.png
	diff images/gridColorPickerTest.png soln_images/gridColorPickerTest.png
	diff images/solidColorPickerTest.png soln_images/solidColorPickerTest.png
	diff images/pacManBFS.png soln_images/pacManBFS.png
	diff images/pacManDFS.png soln_images/pacManDFS.png

mydiffAll: mydiffFrames mydiffImages

.PHONY: all mp4.1 mp4.2 tidy clean
