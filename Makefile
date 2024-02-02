CXX := g++
CXXFLAGS := -std=c++17 -Wall -I/usr/local/include/opencv4
LDFLAGS := -L/usr/local/lib
LDLIBS := -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_video -lstdc++fs -lopencv_videoio -lstdc++fs

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
EXEC := $(BINDIR)/myprogram

$(EXEC): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)