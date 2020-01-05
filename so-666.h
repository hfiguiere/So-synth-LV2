/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * so-666.h
 *
 * Copyright (C) 2011 - Jeremy Salwen
 * Copyright (C) 2010 - 50m30n3
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <lv2.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lv2/lv2plug.in/ns/ext/event/event-helpers.h"
#include "lv2/lv2plug.in/ns/ext/uri-map/uri-map.h"

#define NUMNOTES 80
#define BASENOTE 21

#define MIDI_COMMANDMASK 0xF0
#define MIDI_CHANNELMASK 0x0F

#define MIDI_NOTEON 0x90
#define MIDI_NOTEOFF 0x80
#define MIDI_CONTROL 0xB0

enum PORTS {
  PORT_OUTPUT = 0,
  PORT_MIDI,
  PORT_CONTROLMODE,
  PORT_FEEDBACK,
  PORT_RESONANCE,
  PORT_CUTOFF,
  PORT_VOLUME,
  PORT_CHANNEL
};

void runSO_666(LV2_Handle arg, uint32_t nframes);
LV2_Handle instantiateSO_666(const LV2_Descriptor* descriptor, double s_rate,
                             const char* path,
                             const LV2_Feature* const* features);
void cleanupSO_666(LV2_Handle instance);
void connectPortSO_666(LV2_Handle instance, uint32_t port, void* data_location);

static LV2_Descriptor so_666_Descriptor = {
    .URI = "urn:50m30n3:plugins:SO-666",
    .instantiate = instantiateSO_666,
    .connect_port = connectPortSO_666,
    .activate = NULL,
    .run = runSO_666,
    .deactivate = NULL,
    .cleanup = cleanupSO_666,
    .extension_data = NULL,
};

typedef struct so_666_t {
  float* output;
  LV2_Event_Buffer* MidiIn;
  LV2_Event_Iterator in_iterator;

  LV2_Event_Feature* event_ref;
  int midi_event_id;

  float* controlmode_p;
  float* volume_p;
  float* feedback_p;
  float* resonance_p;
  float* cutoff_p;

  float* strings[NUMNOTES];
  unsigned int stringpos[NUMNOTES];
  unsigned int stringlength[NUMNOTES];
  float stringcutoff[NUMNOTES];
  int status[NUMNOTES];

  unsigned int volume;

  float lpval, lplast;
  float hpval, hplast;
  float fcutoff, freso, ffeedback;

  float* channel_p;
} so_666;
