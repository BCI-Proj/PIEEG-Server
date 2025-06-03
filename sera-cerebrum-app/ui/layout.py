import dearpygui.dearpygui as dpg
from .callbacks import handle_submit


def create_main_window():
    dpg.create_context();
    dpg.create_viewport(title='Sera Cerebrum App', width=800, height=600)
    with dpg.window(label="Main Window"):
        dpg.add_text("Welcome to Dear PyGui!")
        dpg.add_input_text(label="Your Name", tag="InputName")
        dpg.add_button(label="Submit", callback=handle_submit)

