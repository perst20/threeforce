#include <GL/glew.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <iostream>
#include <unistd.h>
#include <shader.h>
#include <geometry.h>
#include <triangles.h>


const size_t MAX_TRIANGLES = 1024;
const color DEFAULT_COLOR = {0.444f, 0.0f, 0.7f, 0.0f};
const color CLICK_COLOR = {0.7f, 1.0f, 0.7f, 0.0f};

Display *display;
GLXContext glxContext;
Window window;
int width = 800, height = 600;


void init_glx_context(int x, int y, int width, int height) {
    Window root;
    XVisualInfo *visualInfo;
    Colormap colormap;
    XSetWindowAttributes setWindowAttributes;
    GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, None};

    if (!(display = XOpenDisplay(NULL))) {
        throw std::runtime_error("error: failed to open display");
    }

    if (!(visualInfo = glXChooseVisual(display, DefaultScreen(display), att))) {
        throw std::runtime_error("error: no appropriate visual found");
    }

    root = RootWindow (display, DefaultScreen(display));

    colormap = XCreateColormap(display, root, visualInfo->visual, AllocNone);

    setWindowAttributes.colormap = colormap;
    setWindowAttributes.event_mask =
            ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask;

    window = XCreateWindow(
            display,
            root,
            x,          //X
            y,          //Y
            width,        //WIDTH
            height,        //HEIGHT
            0,          //BORDER_WIDTH
            visualInfo->depth,
            InputOutput,
            visualInfo->visual,
            CWColormap | CWEventMask,
            &setWindowAttributes
    );

    XMapWindow(display, window);
    XStoreName(display, window, "threeforce");

    glxContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
    glXMakeCurrent(display, window, glxContext);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("error: failed to initialize GLEW");
    }
}

void destroy_context() {
    glXMakeCurrent(display, None, NULL);
    glXDestroyContext(display, glxContext);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

void update_viewport() {
    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, window, &windowAttributes);
    width = windowAttributes.width;
    height = windowAttributes.height;
    glViewport(0, 0, width, height);
}

void set_background_color(color clr) {
    glClearColor(clr.r, clr.g, clr.b, clr.a);
}

int main() {
    init_glx_context(0, 0, width, height);
    GLuint program = create_program("vertex_shader.glsl", "fragment_shader.glsl");
    triangles trs(program, MAX_TRIANGLES);
    int now_tr;
    point prev_cursor_pos{0, 0};
    bool is_button_pressed = false;
    XEvent event;
    auto wm_delete_window_msg = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wm_delete_window_msg, 1);
    set_background_color(DEFAULT_COLOR);

    while (true) {
        if (XCheckTypedEvent(display, ClientMessage, &event) && event.xclient.data.l[0] == wm_delete_window_msg){
            break;
        }
        if (XCheckTypedEvent(display, Expose, &event)) {
            update_viewport();
        }
        if (XCheckTypedEvent(display, ButtonPress, &event)) {
            point norm_pos = get_normalized_point(event.xbutton.x, event.xbutton.y, width, height);
            now_tr = trs.get_triangle_index_by_point(norm_pos);
            if (now_tr == -1) {
                now_tr = (int) trs.size();
                trs.push_back({
                                      norm_pos,
                                      norm_pos - point{0.05f, 0.1f},
                                      norm_pos + point{0.05f, -0.1f}
                });
            }
            set_background_color(CLICK_COLOR);
            prev_cursor_pos = norm_pos;
            is_button_pressed = true;
        } else if (is_button_pressed) {
            int x, y;
            Window root_return, child_return;
            int root_x_return, root_y_return;
            unsigned int mask_return;
            XQueryPointer(display, window, &root_return, &child_return, &root_x_return, &root_y_return, &x, &y,
                          &mask_return);
            point norm_pos = get_normalized_point(x, y, width, height);
            trs.set(now_tr, trs.get(now_tr).move(norm_pos - prev_cursor_pos));
            prev_cursor_pos = norm_pos;
        }
        if (XCheckTypedEvent(display, ButtonRelease, &event)) {
            is_button_pressed = false;
            set_background_color(DEFAULT_COLOR);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        trs.draw();
        glXSwapBuffers(display, window);
    }
    destroy_context();
    return 0;
}
