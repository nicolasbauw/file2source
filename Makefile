CC = clang
LDFLAGS = -lc++ -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

all: main.o bin2source.o imgui.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl2.o imgui_widgets.o
	$(CC) -o file2source main.o imgui.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl2.o imgui_widgets.o $(LDFLAGS)

main.o:
	$(CC) -c main.cpp -I. -Iimgui -Iimgui/examples

bin2source.o:
	$(CC) -c bin2source.c

imgui.o:
	$(CC) -c imgui/imgui.cpp

imgui_draw.o:
	$(CC) -c imgui/imgui_draw.cpp

imgui_impl_glfw.o:
	$(CC) -c imgui/examples/imgui_impl_glfw.cpp -Iimgui

imgui_impl_opengl2.o:
	$(CC) -c imgui/examples/imgui_impl_opengl2.cpp -Iimgui

imgui_widgets.o:
	$(CC) -c imgui/imgui_widgets.cpp

clean:
	rm file2source *.o
