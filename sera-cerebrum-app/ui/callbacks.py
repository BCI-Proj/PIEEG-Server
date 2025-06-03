import dearpygui.dearpygui as dpg;
from dearpygui import *;

def handle_submit(sender, app_data, user_data):
    name = dpg.get_value("Input Name");
    dpg.set_value("InputName", "");
    