#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>
#include <stdio.h>
#include <string.h>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "defs.h"
#include "raw2source.c"
#include "bin2source.c"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(760,190, "File2source", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = NULL;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    bool show_main_window = true;
    ImGuiWindowFlags window_flags = 0;
    ImVec4 clear_color = ImColor(0.7f, 0.7f, 0.7f);

    // Main loop
    while (!glfwWindowShouldClose(window) && !quit)
    {
        glfwPollEvents();
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Interface display
        ImGui::SetNextWindowSize(ImVec2(760,190));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        window_flags |= ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoMove;
        ImGui::Begin("File2source", &show_main_window,window_flags);
        //ImGui::PushID(i);
        /*ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(i/7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(i/7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(i/7.0f, 0.8f, 0.8f));*/
        if (ImGui::Button("Select binary or RAW file")) {};
        ImGui::SameLine();ImGui::InputText("Input", InputFile, 100);
        if (ImGui::Button("  Select C source file   ")) {};
        ImGui::SameLine();ImGui::InputText("Output", OutputFile, 100);
        ImGui::Button("    UINT8 array name     ");ImGui::SameLine();ImGui::InputText("Array", table, 16);
        ImGui::Button("Enter RAW width / height ");ImGui::SameLine();ImGui::InputInt2("W/H", rawsize);
        ImGui::Checkbox("UINT8 typedef", &uint8def);ImGui::SameLine();ImGui::Checkbox("File is a RAW image", &raw);ImGui::SameLine();//ImGui::Checkbox("Convert to RGBA", &rgbaconvert);
        ImGui::SameLine();ImGui::Text("      RAW is:");ImGui::SameLine();ImGui::RadioButton("24 bits", &bpp, 0);ImGui::SameLine();ImGui::RadioButton("32 bits", &bpp, 1);ImGui::SameLine();ImGui::RadioButton("24->32 conversion", &bpp, 3);
        ImGui::ColorEdit3("Transparent color for RGBA conv.", col1);
        ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();ImGui::Text("1.1                                        ");ImGui::SameLine();
        if (ImGui::Button("  Quit  ")) { quit = 1; }
        ImGui::SameLine();
        if (ImGui::Button("Generate")) {if (raw == true) result = raw2source(); if (raw == false) result = bin2source();};
        //ImGui::PopStyleColor(3);
        //ImGui::PopID();
        if (result == 0) ShowOverlay(&show_app_fixed_overlay);
        if (result == 1) ShowOverlay(&show_app_fixed_overlay);
        if (result == 2) ShowOverlay(&show_app_fixed_overlay);
        ImGui::End();
        
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

/*Filename requester
void GetFileName()
{
        // open a file name
    	ZeroMemory( &ofn , sizeof( ofn));
    	ofn.lStructSize = sizeof ( ofn );
    	ofn.hwndOwner = NULL  ;
    	ofn.lpstrFile = szFile ;
    	ofn.lpstrFile[0] = '\0';
    	ofn.nMaxFile = sizeof( szFile );
    	ofn.lpstrFilter = "All\0*.*\0RAW\0*.RAW\0C source\0*.c\0";
    	ofn.nFilterIndex =1;
    	ofn.lpstrFileTitle = NULL ;
    	ofn.nMaxFileTitle = 0 ;
    	ofn.lpstrInitialDir=NULL ;
    	GetOpenFileName( &ofn );
    };*/

// Messages display
static void ShowOverlay(bool* opened)
{
    ImGui::SetNextWindowPos(ImVec2(542,148));
    if (!ImGui::Begin("Example: Fixed Overlay"))
    {
        ImGui::End();
        return;
    }
    if (result == 0) ImGui::Text("Successfully wrote C source !");
    if (result == 1) ImGui::Text("     Read / write error !    ");
    if (result == 2) ImGui::Text("  Enter RAW width / height ! ");
    if (ImGui::IsMouseClicked(0)) result=3;
    ImGui::Separator();
    ImGui::Text("   Press left mouse button   ");
    ImGui::End();
}

