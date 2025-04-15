from esphome import automation
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

DEPENDENCIES = ["spi"]
CODEOWNERS = ["@folhas99"]

cc1101_ns = cg.esphome_ns.namespace("cc1101")
CC1101Component = cc1101_ns.class_("CC1101Component", cg.Component, sensor.Sensor)

CONFIG_SCHEMA = sensor.sensor_schema().extend({
    cv.GenerateID(): cv.declare_id(CC1101Component),
    cv.Required("sck_pin"): cv.int_,
    cv.Required("miso_pin"): cv.int_,
    cv.Required("mosi_pin"): cv.int_,
    cv.Required("csn_pin"): cv.int_,
    cv.Required("gdo0_pin"): cv.int_,
    cv.Required("gdo2_pin"): cv.int_,
    cv.Required("bandwidth"): cv.float_,
    cv.Required("frequency"): cv.float_,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID],
        config["sck_pin"], config["miso_pin"], config["mosi_pin"],
        config["csn_pin"], config["gdo0_pin"], config["gdo2_pin"],
        config["bandwidth"], config["frequency"]
    )
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
