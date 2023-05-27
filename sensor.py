import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, binary_sensor, text_sensor, select # TODO: text_sensor, select, number, button
from esphome.const import (
    CONF_ID,
    CONF_TIMEOUT,
    CONF_BINARY,
    DEVICE_CLASS_PRESENCE,
    DEVICE_CLASS_MOTION
)
from esphome import automation
from esphome.automation import maybe_simple_id

DEPENDENCIES = ["uart", "text_sensor", "binary_sensor", "select"]
CODEOWNERS = ["@kamholtz"]
# MULTI_CONF = True

r24avd1_ns = cg.esphome_ns.namespace("r24avd1")
R24AVD1Component = r24avd1_ns.class_("R24AVD1Component", cg.Component, uart.UARTDevice)
# R24AVD1Restart = r24avd1_ns.class_("R24AVD1Restart", automation.Action)
CONF_R24AVD1_ID = "r24avd1_id"

# CONF_MAX_MOVE_DISTANCE = "max_move_distance"
# CONF_MAX_STILL_DISTANCE = "max_still_distance"

# DISTANCES = [0.75, 1.5, 2.25, 3, 3.75, 4.5, 5.25, 6]

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
            cv.Optional(CONF_HAS_SCENE): select.select_schema(
                # device_class=DEVICE_CLASS_SCENE
            ),
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)

# CONFIG_SCHEMA = (
#     cv.Schema(
#         {
#             cv.GenerateID(): cv.declare_id(MHZ19Component),
#             cv.Required(CONF_CO2): sensor.sensor_schema(
#                 unit_of_measurement=UNIT_PARTS_PER_MILLION,
#                 icon=ICON_MOLECULE_CO2,
#                 accuracy_decimals=0,
#                 device_class=DEVICE_CLASS_CARBON_DIOXIDE,
#                 state_class=STATE_CLASS_MEASUREMENT,
#             ),
#             cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
#                 unit_of_measurement=UNIT_CELSIUS,
#                 accuracy_decimals=0,
#                 device_class=DEVICE_CLASS_TEMPERATURE,
#                 state_class=STATE_CLASS_MEASUREMENT,
#             ),
#             cv.Optional(CONF_AUTOMATIC_BASELINE_CALIBRATION): cv.boolean,
#         }
#     )
#     .extend(cv.polling_component_schema("60s"))
#     .extend(uart.UART_DEVICE_SCHEMA)
# )


# DONE
FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "r24avd1",
    baud_rate=9600,
    # data_bits=8,
    require_tx=True,
    require_rx=True,
    parity="NONE",
    stop_bits=1,
)


scene_options = [
    "Default (0x00)",
    "Area detection (top mounted) (0x01)",
    "Toilet (top mounted) (0x02)",
    "Bedroom (top loading) (0x03)",
    "Bedroom (top mounted) (0x04)",
    "Bedroom (top mounted) (0x05)"
]

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID]) # TODO: what is this
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    # sens = await text_sensor.new_text_sensor(config[CONF])
    # cg.add(var.set_approach_sensor(sens))

    if CONF_HAS_PRESENCE in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_HAS_PRESENCE])
        cg.add(var.set_presence_binary_sensor(sens))
    if CONF_HAS_MOTION in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_HAS_MOTION])
        cg.add(var.set_motion_binary_sensor(sens))
    if CONF_HAS_APPROACH in config:
        sens = await text_sensor.new_text_sensor(config[CONF_HAS_APPROACH])
        cg.add(var.set_approach_text_sensor(sens))
    if CONF_HAS_SCENE in config:
        # sens = await select.new_select(config[CONF_HAS_SCENE], options=scene_options)
        sens = await select.new_select(config[CONF_HAS_SCENE], options=list(scene_options))
        await cg.register_component(sens, config[CONF_HAS_SCENE])
        cg.add(sens.set_select_mappings(list(scene_options)))
        # cg.add(var.set_scene_select(sens))

        # var = await select.new_select(config, options=list(options_map.values()))
        # await cg.register_component(var, config)
        # cg.add(var.set_select_mappings(list(options_map.keys())))




CALIBRATION_ACTION_SCHEMA = maybe_simple_id(
    {
        cv.Required(CONF_ID): cv.use_id(R24AVD1Component),
    }
)



