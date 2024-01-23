local _2afile_2a = "C:\\Users\\carlk\\repos\\esphome-radar/.lnvim.fnl"
local _2amodule_name_2a = "overseer-commands"
local _2amodule_2a
do
  package.loaded[_2amodule_name_2a] = {}
  _2amodule_2a = package.loaded[_2amodule_name_2a]
end
local _2amodule_locals_2a
do
  _2amodule_2a["aniseed/locals"] = {}
  _2amodule_locals_2a = (_2amodule_2a)["aniseed/locals"]
end
local autoload = (require("nvim-local-fennel.aniseed.autoload")).autoload
local a, config_fs, config_overseer, fs, nvim, overseer, path, scandir, str = autoload("nvim-local-fennel.aniseed.core"), autoload("config.fs"), autoload("config.plugin.overseer"), autoload("aniseed.fs"), autoload("nvim-local-fennel.aniseed.nvim"), autoload("overseer"), autoload("plenary.path"), autoload("plenary.scandir"), autoload("nvim-local-fennel.aniseed.string")
do end (_2amodule_locals_2a)["a"] = a
_2amodule_locals_2a["config-fs"] = config_fs
_2amodule_locals_2a["config-overseer"] = config_overseer
_2amodule_locals_2a["fs"] = fs
_2amodule_locals_2a["nvim"] = nvim
_2amodule_locals_2a["overseer"] = overseer
_2amodule_locals_2a["path"] = path
_2amodule_locals_2a["scandir"] = scandir
_2amodule_locals_2a["str"] = str
local function _1_(params)
  return {cmd = {"esphome"}, args = {"run", "--device", "esphome-web-ac358c.local", "esphome-web-ac358c.yaml"}, name = "esphome run radar OFFICE", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome run radar OFFICE", builder = _1_})
local function _2_(params)
  return {cmd = {"esphome"}, args = {"compile", "--only-generate", "esphome-web-ac358c.yaml"}, name = "esphome compile --only-generate radar OFFICE", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome compile --only-generate radar OFFICE", builder = _2_})
local function _3_(params)
  return {cmd = {"esphome"}, args = {"compile", "esphome-web-ac358c.yaml"}, name = "esphome compile radar OFFICE", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome compile radar OFFICE", builder = _3_})
local function _4_(params)
  return {cmd = {"esphome"}, args = {"clean", "esphome-web-ac358c.yaml"}, name = "esphome clean radar OFFICE", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome clean radar OFFICE", builder = _4_})
local function _5_(params)
  return {cmd = {"esphome"}, args = {"logs", "esphome-web-ac358c.yaml", "--client-id", "esphome-web-ac358c.local"}, name = "esphome clean radar OFFICE", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome log radar OFFICE", builder = _5_})
local function _6_(params)
  return {cmd = {"esphome"}, args = {"run", "--device", "esphome-web-998ec8.local", "esphome-web-998ec8.yaml"}, name = "esphome run radar LOUNGE", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome run radar LOUNGE", builder = _6_})
local function _7_(params)
  return {cmd = {"esphome"}, args = {"compile", "--only-generate", "esphome-web-998ec8.yaml"}, name = "esphome compile radar LOUNGE", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome compile radar LOUNGE", builder = _7_})
local function _8_(params)
  return {cmd = {"esphome"}, args = {"clean", "esphome-web-998ec8.yaml"}, name = "esphome clean radar", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome clean radar LOUNGE", builder = _8_})
local function _9_(params)
  return {cmd = {"esphome"}, args = {"logs", "esphome-web-998ec8.yaml", "--client-id", "esphome-web-998ec8.local"}, name = "esphome clean radar LOUNGE", env = {}, cwd = vim.fn.expand("%:h")}
end
overseer.register_template({name = "esphome log radar LOUNGE", builder = _9_})
return _2amodule_2a