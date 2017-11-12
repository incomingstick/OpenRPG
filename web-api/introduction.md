---
layout: docs
title: Introduction
description: Learn how to use and host OpenRPG API
group: web-api
redirect_from: "/api/"
---
<!-- Copied from README.md -->
[![Build Status](https://travis-ci.org/incomingstick/OpenRPG.svg?branch=master)](https://travis-ci.org/incomingstick/OpenRPG)
![Version Number](https://img.shields.io/badge/version-v0.4.2--dev-blue.svg)
[![Build status](https://ci.appveyor.com/api/projects/status/jhcr2ebcws32bs2m?svg=true)](https://ci.appveyor.com/project/incomingstick/openrpg)

Currently OpenRPG API in under active development, as OpenRPG updates
with new modules and features. The API will be updated to accommodate them.
The API works as a thin wrapper around the existing OpenRPG modules, but
gives you the ability to use the modules within an internet browser.
The API is currently written in Rust and utilizes the Rocket framework for all
Interactions and hosting.

Some of the current features of the API are:

- A restfull api for interacting with OpenRPG modules
- Currently supported modules are roll and name modules