all: main.o bin2source.o imgui.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl2.o imgui_widgets.o
	clang -o file2source main.o imgui.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl2.o imgui_widgets.o -lc++ -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

main.o:
	clang -c main.cpp -I. -Iimgui -Iimgui/examples

imgui.o:
	clang -c imgui/imgui.cpp

imgui_draw.o:
	clang -c imgui/imgui_draw.cpp

imgui_impl_glfw.o:
	clang -c imgui/examples/imgui_impl_glfw.cpp -Iimgui

imgui_impl_opengl2.o:
	clang -c imgui/examples/imgui_impl_opengl2.cpp -Iimgui

imgui_widgets.o:
	clang -c imgui/imgui_widgets.cpp

clean:
	rm file2source *.o
