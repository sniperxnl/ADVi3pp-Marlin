/**
 * Marlin 3D Printer Firmware For Wanhao Duplicator i3 Plus (ADVi3++)
 *
 * Copyright (C) 2017 Sebastien Andrivet [https://github.com/andrivet/]
 *
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef ADV_I3_PLUS_PLUS_PRIVATE_H
#define ADV_I3_PLUS_PLUS_PRIVATE_H

#include "adv_i3_plus_plus_enums.h"

namespace advi3pp { inline namespace internals {

enum class BackgroundTask: uint8_t
{
    None                = 0,
    LevelInit           = 1,
    LoadFilament        = 2,
    UnloadFilament      = 3,
    Move                = 4
};

// --------------------------------------------------------------------
// Preset
// --------------------------------------------------------------------

//! Hostend and bad temperature preset.
struct Preset
{
    uint16_t hotend;
    uint16_t bed;
};

// --------------------------------------------------------------------
// i3PlusPrinterImpl
// --------------------------------------------------------------------

//! Implementation of the Duplication i3 Plus printer and its LCD
class i3PlusPrinterImpl
{
public:
    void setup();
    void task();
    void show_page(Page page);
    void update_graph_data();
    void auto_pid_finished();
    void store_presets(eeprom_write write, int& eeprom_index, uint16_t& working_crc);
    void restore_presets(eeprom_read read, int& eeprom_index, uint16_t& working_crc);
    void reset_presets();
    void temperature_error();

private:
    void send_versions();
    void execute_background_task();
    void leveling_init();
    void unload_filament();
    void load_filament();
    void send_status_update();
    Page get_current_page();
    void read_lcd_serial();
    void send_stats();
    template<size_t S> void get_file_name(uint8_t index, Chars<S>& name);
    Chars<16> get_lcd_firmware_version();
    void set_next_background_task_time(unsigned int delta = 500);
    void set_next_update_time(unsigned int delta = 500);

private: // Actions
    void sd_card(KeyValue key_value);
    void sd_card_select_file(KeyValue key_value);
    void print_stop(KeyValue key_value);
    void print_pause(KeyValue key_value);
    void print_resume(KeyValue key_value);
    void preheat(KeyValue key_value);
    void cooldown(KeyValue key_value);
    void motors_or_pid_settings(KeyValue key_value);
    void save_motors_or_pid_settings(KeyValue key_value);
    void factory_reset(KeyValue key_value);
    void print_settings(KeyValue key_value);
    void save_print_settings(KeyValue key_value);
    void load_unload_back(KeyValue key_value);
    void level(KeyValue key_value);
    void filament(KeyValue key_value);
    void move_x_plus(KeyValue key_value);
    void move_x_minus(KeyValue key_value);
    void move_y_plus(KeyValue key_value);
    void move_y_minus(KeyValue key_value);
    void move_z_plus(KeyValue key_value);
    void move_z_minus(KeyValue key_value);
    void move_e_plus(KeyValue key_value);
    void move_e_minus(KeyValue key_value);
    void disable_motors(KeyValue key_value);
    void home_X(KeyValue key_value);
    void home_y(KeyValue key_value);
    void home_z(KeyValue key_value);
    void home_all(KeyValue key_value);
    void statistics(KeyValue key_value);
    void pid_tuning(KeyValue key_value);
    void temperature_graph(KeyValue key_value);
    void print(KeyValue key_value);
    void about(KeyValue key_value);
    void lcd_update_mode(KeyValue key_value);

private:
    static const size_t NB_PRESETS = 3;

    uint16_t last_file_index_ = 0;
    millis_t next_op_time_ = 0;
    millis_t next_update_time_ = 0;
    BackgroundTask background_task_ = BackgroundTask::None;
    bool temp_graph_update_ = false;
    Page last_page_ = Page::None;
    Preset presets_[NB_PRESETS];
    uint16_t adv_i3_pp_lcd_version_ = 0x0000;
};

}}

#endif //ADV_I3_PLUS_PLUS_PRIVATE_H

