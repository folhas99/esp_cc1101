import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import spi
from esphome.const import CONF_ID

cc1101_ns = cg.esphome_ns.namespace('cc1101')
CC1101Component = cc1101_ns.class_('CC1101Component', cg.Component)

CONF_SCK = "sck_pin"
CONF_MISO = "miso_pin"
CONF_MOSI = "mosi_pin"
CONF_CSN = "csn_pin"
CONF_GDO0 = "gdo0_pin"
CONF_GDO2 = "gdo2_pin"
CONF_BW = "bandwidth"
CONF_FREQ = "frequency"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(CC1101Component),
    cv.Required(CONF_SCK): pins.gpio_output_pin_schema,
    cv.Required(CONF_MISO): pins.gpio_input_pin_schema,
    cv.Required(CONF_MOSI): pins.gpio_output_pin_schema,
    cv.Required(CONF_CSN): pins.gpio_output_pin_schema,
    cv.Required(CONF_GDO0): pins.gpio_output_pin_schema,
    cv.Required(CONF_GDO2): pins.gpio_input_pin_schema,
    cv.Required(CONF_BW): cv.float_range(min=1.0, max=1000.0),
    cv.Required(CONF_FREQ): cv.float_range(min=300.0, max=1000.0),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID],
                           await cg.gpio_pin_expression(config[CONF_SCK]),
                           await cg.gpio_pin_expression(config[CONF_MISO]),
                           await cg.gpio_pin_expression(config[CONF_MOSI]),
                           await cg.gpio_pin_expression(config[CONF_CSN]),
                           await cg.gpio_pin_expression(config[CONF_GDO0]),
                           await cg.gpio_pin_expression(config[CONF_GDO2]),
                           config[CONF_BW],
                           config[CONF_FREQ])
    await cg.register_component(var, config)
