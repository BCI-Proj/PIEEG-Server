from ui.layout import create_main_window;
import dearpygui.dearpygui as dpg;

create_main_window();
dpg.setup_dearpygui();
dpg.show_viewport();
dpg.start_dearpygui();
dpg.destroy_context();




