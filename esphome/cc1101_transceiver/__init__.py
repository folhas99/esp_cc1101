
from esphome.components import sensor
import esphome.config_validation as cv
import esphome.codegen as cg

cc1101_ns = cg.esphome_ns.namespace('cc1101_transceiver')
CC1101Component = cc1101_ns.class_('CC1101Component', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(CC1101Component),
    cv.Required("sck"): cv.int_,
    cv.Required("miso"): cv.int_,
    cv.Required("mosi"): cv.int_,
    cv.Required("csn"): cv.int_,
    cv.Required("gdo0"): cv.int_,
    cv.Required("gdo2"): cv.int_,
    cv.Required("frequency"): cv.float_,
    cv.Required("bandwidth"): cv.int_,
})

async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()],
                           config["sck"], config["miso"], config["mosi"],
                           config["csn"], config["gdo0"], config["gdo2"],
                           config["frequency"], config["bandwidth"])
    await cg.register_component(var, config)
