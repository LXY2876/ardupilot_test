/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *   Airspeed.cpp - airspeed example sketch
 *
 */

#include <AP_AOA/AP_AOA.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_BoardConfig/AP_BoardConfig.h>
#include <GCS_MAVLink/GCS_Dummy.h>

void setup();
void loop();

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

float temperature;

// create an AHRS object for get_airspeed_max
// AP_AHRS ahrs;

// create airspeed object

// AS_5600 as5600;
AP_Aoa aoa;
static AP_BoardConfig board_config;

namespace {
// try to set the object value but provide diagnostic if it failed
void set_object_value(const void *object_pointer,
                      const struct AP_Param::GroupInfo *group_info,
                      const char *name, float value)
{
    if (!AP_Param::set_object_value(object_pointer, group_info, name, value)) {
        hal.console->printf("WARNING: AP_Param::set object value \"%s::%s\" Failed.\n",
                            group_info->name, name);
    }
}
}

// to be called only once on boot for initializing objects
void setup()
{
    
    // set airspeed pin to 65, enable and use to true
    // set_object_value(&airspeed, airspeed.var_info, "PIN", 65);
    set_object_value(&aoa, aoa.var_info, "ENABLE", 1);
    set_object_value(&aoa, aoa.var_info, "USE", 1);
    aoa.set_param_type(1);
    board_config.init();
    hal.console->printf("ArduPilot AOA library test\n");
    // as5600.init();
    // as5600.checkConnect();
    // initialize airspeed
    // Note airspeed.set_log_bit(LOG_BIT) would need to be called in order to enable logging
    // airspeed.init();
    aoa.init();
    aoa.calibrate(false);
}

// loop
void loop(void)
{
    static uint32_t timer;

    // run read() and get_temperature() in 10Hz
    if ((AP_HAL::millis() - timer) > 100) {
        // // current system time in milliseconds
        // timer = AP_HAL::millis();
        // airspeed.update();
        // airspeed.get_temperature(temperature);
        // print temperature and airspeed to console
        // hal.console->printf("aoa =%d\n",
        //                     as5600.getRawAngle());
        // hal.console->printf("hello world\n");
        // as5600.checkConnect();
                // current system time in milliseconds
        timer = AP_HAL::millis();
        aoa.update();
        aoa.get_temperature(temperature);

        // print temperature and airspeed to console
        hal.console->printf("airspeed %5.2f temperature %6.2f healthy = %u\n",
                            (double)aoa.get_aoa(), (double)temperature, aoa.healthy());
        // hal.console->printf("hello world");
      
        // hal.console->printf("sensor = %d",aoa.get_param_bus() );

    }
    hal.scheduler->delay(1);
}

const struct AP_Param::GroupInfo        GCS_MAVLINK_Parameters::var_info[] = {
    AP_GROUPEND
};
GCS_Dummy _gcs;

AP_HAL_MAIN();
