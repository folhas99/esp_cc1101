from esphome.components import sensor
import esphome.config_validation as cv
import esphome.codegen as cg

cc1101_ns = cg.esphome_ns.namespace('cc1101')
CC1101Component = cc1101_ns.class_('CC1101Component', cg.PollingComponent, sensor.Sensor)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(CC1101Component),
    cv.Required("sck_pin"): cv.gpio_pin,
    cv.Required("miso_pin"): cv.gpio_pin,
    cv.Required("mosi_pin"): cv.gpio_pin,
    cv.Required("cs_pin"): cv.gpio_pin,
    cv.Required("gdo0_pin"): cv.gpio_pin,
    cv.Required("gdo2_pin"): cv.gpio_pin,
    cv.Required("bandwidth"): cv.float_,
    cv.Required("frequency"): cv.float_,
})

async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    cg.add(var.set_pins(
        config["sck_pin"].number,
        config["miso_pin"].number,
        config["mosi_pin"].number,
        config["cs_pin"].number,
        config["gdo0_pin"].number,
        config["gdo2_pin"].number
    ))

    cg.add(var.set_bandwidth(config["bandwidth"]))
    cg.add(var.set_frequency(config["frequency"]))
