import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, binary_sensor, text_sensor, select # TODO: text_sensor, select, number, button
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_PRESENCE,
    DEVICE_CLASS_MOTION
)

DEPENDENCIES = ["text_sensor", "binary_sensor"]
CODEOWNERS = ["@kamholtz"]

r24avd1_ns = cg.esphome_ns.namespace("r24avd1")
R24AVD1Component = r24avd1_ns.class_("R24AVD1Component", cg.Component, uart.UARTDevice)
CONF_R24AVD1_ID = "r24avd1_id"


CONF_HAS_PRESENCE = "has_presence"
CONF_HAS_MOTION = "has_motion"
CONF_HAS_APPROACH = "has_approach"
CONF_HAS_SCENE = "has_scene"


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(R24AVD1Component),

            cv.Optional(CONF_HAS_PRESENCE): binary_sensor.binary_sensor_schema(
                # TODO: Can I put name here so it always appears?
                device_class=DEVICE_CLASS_PRESENCE
            ),
            cv.Optional(CONF_HAS_MOTION): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_MOTION
            ),
            cv.Optional(CONF_HAS_APPROACH): text_sensor.text_sensor_schema(
                # icon=ICON_ACCURACY # TODO: find icon to use here
            ),
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "r24avd1",
    baud_rate=9600,
    # data_bits=8,
    require_tx=True,
    require_rx=True,
    parity="NONE",
    stop_bits=1,
)


async def to_code(config):
    scene_options = [
        "Default (0x00)",
        "Area detection (top mounted) (0x01)",
        "Toilet (top mounted) (0x02)",
        "Bedroom (top loading) (0x03)",
        "Bedroom (top mounted) (0x04)",
        "Bedroom (top mounted) (0x05)"
    ]

    var = cg.new_Pvariable(config[CONF_ID]) # TODO: what is this
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_HAS_PRESENCE in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_HAS_PRESENCE])
        cg.add(var.set_presence_binary_sensor(sens))
    if CONF_HAS_MOTION in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_HAS_MOTION])
        cg.add(var.set_motion_binary_sensor(sens))
    if CONF_HAS_APPROACH in config:
        sens = await text_sensor.new_text_sensor(config[CONF_HAS_APPROACH])
        cg.add(var.set_approach_text_sensor(sens))
