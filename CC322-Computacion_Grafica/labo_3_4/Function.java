import org.lwjgl.*;
import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;
 
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;
 
public class HelloWorld {
 
    private GLFWErrorCallback errorCallback;
    private GLFWKeyCallback   keyCallback;
 
    private long window;
 
    public void run() {
        System.out.println("Hello labro_3_4_Grafica " + Version.getVersion() + "!");
 
        try {
            init();
            loop();
 
            glfwDestroyWindow(window);
            keyCallback.release();
        } finally {
            glfwTerminate();
            errorCallback.release();
        }
    }
 
    private void init() {
        glfwSetErrorCallback(errorCallback = GLFWErrorCallback.createPrint(System.err));
 
        if ( glfwInit() != GLFW_TRUE )
            throw new IllegalStateException("Unable to initialize GLFW");
 
        glfwDefaultWindowHints(); // optional, the current window hints are already the default
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // the window will stay hidden after creation
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); // the window will be resizable
 
        int WIDTH = 300;
        int HEIGHT = 300;
 
        // Create the window
        window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World!", NULL, NULL);
        if ( window == NULL )
            throw new RuntimeException("Failed to create the GLFW window");
 
        // Setup a key callback. It will be called every time a key is pressed, repeated or released.
        glfwSetKeyCallback(window, keyCallback = new GLFWKeyCallback() {
            @Override
            public void invoke(long window, int key, int scancode, int action, int mods) {
                if ( key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE )
                    glfwSetWindowShouldClose(window, GLFW_TRUE); // We will detect this in our rendering loop
            }
        });
 
        // Get the resolution of the primary monitor
        GLFWVidMode vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        // Center our window
        glfwSetWindowPos(
            window,
            (vidmode.width() - WIDTH) / 2,
            (vidmode.height() - HEIGHT) / 2
        );
 
        // Make the OpenGL context current
        glfwMakeContextCurrent(window);
        // Enable v-sync
        glfwSwapInterval(1);
 
        // Make the window visible
        glfwShowWindow(window);
    }
 
    private void loop() {
        GL.createCapabilities();
 
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
 
        while ( glfwWindowShouldClose(window) == GLFW_FALSE ) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer
 
            glfwSwapBuffers(window); // swap the color buffers
 
            glfwPollEvents();
        }
    }
 
    public static void main(String[] args) {
        new HelloWorld().run();
    }
 
}
