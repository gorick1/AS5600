import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_ID,
    UNIT_DEGREES,
    ICON_COMPASS,
    STATE_CLASS_MEASUREMENT,
)

DEPENDENCIES = ["i2c"]
AUTO_LOAD = ["sensor"]

as5600_ns = cg.esphome_ns.namespace("as5600")
AS5600Sensor = as5600_ns.class_(
    "AS5600Sensor", sensor.Sensor, cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        unit_of_measurement=UNIT_DEGREES,
        icon=ICON_COMPASS,
        accuracy_decimals=1,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.GenerateID(): cv.declare_id(AS5600Sensor),
        }
    )
    .extend(i2c.i2c_device_schema(0x36))
    .extend(cv.polling_component_schema("250ms"))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await i2c.register_i2c_device(var, config)
