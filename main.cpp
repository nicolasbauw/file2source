#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>
#include <stdio.h>
#include <string.h>
#include <GLFW/glfw3.h>
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

    ImGuiWindowFlags window_flags = 0;

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
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Border] = ImVec4(0.7f, 0.7f, 0.7f, 0.5f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
        style.FrameBorderSize = 1.0f;
        window_flags |= ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoMove;
        ImGui::Begin("File2source", &show_main_window,window_flags);
        ImGui::PushID(i);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i/7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i/7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i/7.0f, 0.8f, 0.8f));

        // Graphical file requester only on windows
        #ifndef _WIN32
        if (ImGui::Button("Select binary or RAW file")) {};
        #endif
        #ifdef _WIN32
        if (ImGui::Button("Select binary or RAW file")) {GetFileName(); strcpy(InputFile,szFile);};
        #endif
        ImGui::SameLine();ImGui::InputText("Input", InputFile, 100);
        #ifndef _WIN32
        if (ImGui::Button("  Select C source file   ")) {};
        #endif
        #ifdef _WIN32
        if (ImGui::Button("  Select C source file   ")) {GetFileName(); strcpy(OutputFile,szFile);};
        #endif

        ImGui::SameLine();ImGui::InputText("Output", OutputFile, 100);
        ImGui::Button("    UINT8 array name     ");ImGui::SameLine();ImGui::InputText("Array", table, 16);
        ImGui::Button("Enter RAW width / height ");ImGui::SameLine();ImGui::InputInt2("W/H", rawsize);
        ImGui::Checkbox("UINT8 typedef", &uint8def);ImGui::SameLine();ImGui::Checkbox("File is a RAW image", &raw);
        ImGui::SameLine();ImGui::Text("      RAW is:");ImGui::SameLine();ImGui::RadioButton("24 bits", &bpp, 0);ImGui::SameLine();ImGui::RadioButton("32 bits", &bpp, 1);ImGui::SameLine();ImGui::RadioButton("24->32 conversion", &bpp, 3);
        ImGui::ColorEdit3("Transparent color for RGBA conv.", col1);
        ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();ImGui::Spacing();ImGui::Text("1.1                                        ");ImGui::SameLine();
        if (ImGui::Button("  Quit  ")) { quit = 1; }
        ImGui::SameLine();
        if (ImGui::Button("Generate")) {if (raw == true) result = raw2source(); if (raw == false) result = bin2source();};
        ImGui::PopStyleColor(3);
        ImGui::PopID();
        if (result == 0 || result == 1 || result == 2) ShowPopup();
        ImGui::End();
        
        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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

#ifdef _WIN32
//Filename requester
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
    };
#endif

// Messages display
static void ShowPopup()
{
    bool* opened = &show_app_fixed_overlay;
    ImGui::SetNextWindowPos(ImVec2(540,139));
    if (!ImGui::Begin("Example: Fixed Overlay", opened, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav))
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

