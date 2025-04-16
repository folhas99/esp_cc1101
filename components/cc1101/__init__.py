import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

cc1101_ns = cg.esphome_ns.namespace("cc1101")
CC1101Component = cc1101_ns.class_("CC1101Component", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(CC1101Component),
    cv.Required("sck_pin"): cv.gpio_pin,
    cv.Required("miso_pin"): cv.gpio_pin,
    cv.Required("mosi_pin"): cv.gpio_pin,
    cv.Required("csn_pin"): cv.gpio_pin,
    cv.Required("gdo0_pin"): cv.gpio_pin,
    cv.Required("bandwidth_khz"): cv.float_,
    cv.Required("freq_mhz"): cv.float_,
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_pins(
        config["sck_pin"].number,
        config["miso_pin"].number,
        config["mosi_pin"].number,
        config["csn_pin"].number,
        config["gdo0_pin"].number
    ))
    cg.add(var.set_bandwidth(config["bandwidth_khz"]))
    cg.add(var.set_frequency(config["freq_mhz"]))
