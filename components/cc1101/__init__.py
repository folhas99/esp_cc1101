import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ["spi"]
CODEOWNERS = ["@folhas99"]

cc1101_ns = cg.esphome_ns.namespace("cc1101")
CC1101Component = cc1101_ns.class_("CC1101Component", cg.Component)


CONF_SCK_PIN = "sck_pin"
CONF_MISO_PIN = "miso_pin"
CONF_MOSI_PIN = "mosi_pin"
CONF_CSN_PIN = "csn_pin"
CONF_GDO0_PIN = "gdo0_pin"
CONF_GDO2_PIN = "gdo2_pin"
CONF_BANDWIDTH = "bandwidth"
CONF_FREQUENCY = "frequency"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(CC1101Component),
    cv.Required(CONF_SCK_PIN): cv.int_,
    cv.Required(CONF_MISO_PIN): cv.int_,
    cv.Required(CONF_MOSI_PIN): cv.int_,
    cv.Required(CONF_CSN_PIN): cv.int_,
    cv.Required(CONF_GDO0_PIN): cv.int_,
    cv.Required(CONF_GDO2_PIN): cv.int_,
    cv.Required(CONF_BANDWIDTH): cv.float_,
    cv.Required(CONF_FREQUENCY): cv.float_,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID],
        config[CONF_SCK_PIN], config[CONF_MISO_PIN], config[CONF_MOSI_PIN],
        config[CONF_CSN_PIN], config[CONF_GDO0_PIN], config[CONF_GDO2_PIN],
        config[CONF_BANDWIDTH], config[CONF_FREQUENCY]
    )
    await cg.register_component(var, config)
