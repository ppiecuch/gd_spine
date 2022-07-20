/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated January 1, 2020. Replaces all prior versions.
 *
 * Copyright (c) 2013-2020, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THE SPINE RUNTIMES ARE PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES,
 * BUSINESS INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THE SPINE RUNTIMES, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#pragma once

#include "SpineSkeleton.h"
#include "SpineAnimationState.h"
#include "scene/2d/node_2d.h"
#include "scene/2d/mesh_instance_2d.h"

class SpineSlotNode;

class SpineSprite : public Node2D, public spine::AnimationStateListenerObject {
	GDCLASS(SpineSprite, Node2D)

	friend class SpineBone;

protected:
	Ref<SpineSkeletonDataResource> skeleton_data_res;
	Ref<SpineSkeleton> skeleton;
	Ref<SpineAnimationState> animation_state;
	SpineConstant::UpdateMode update_mode;

	String preview_animation;
	bool preview_frame;
	float preview_time;

	bool debug_bones;
	Color debug_bones_color;
	float debug_bones_thickness;
	bool debug_regions;
	Color debug_regions_color;
	bool debug_meshes;
	Color debug_meshes_color;
	bool debug_bounding_boxes;
	Color debug_bounding_boxes_color;
	bool debug_paths;
	Color debug_paths_color;
	bool debug_clipping;
	Color debug_clipping_color;

	spine::Vector<spine::Vector<SpineSlotNode *>> slot_nodes;
	Vector<MeshInstance2D *> mesh_instances;
	static Ref<CanvasItemMaterial> default_materials[4];
	Ref<Material> normal_material;
	Ref<Material> additive_material;
	Ref<Material> multiply_material;
	Ref<Material> screen_material;
	spine::SkeletonClipping *skeleton_clipper;
	bool modified_bones;

	static void _bind_methods();
	void _notification(int what);
	void _get_property_list(List<PropertyInfo> *list) const;
	bool _get(const StringName &property, Variant &value) const;
	bool _set(const StringName &property, const Variant &value);

	void generate_meshes_for_slots(Ref<SpineSkeleton> skeleton_ref);
	void remove_meshes();
	void sort_slot_nodes();
	void update_meshes(Ref<SpineSkeleton> skeleton_ref);
	void set_modified_bones() { modified_bones = true; }
	void draw();
	void draw_bone(spine::Bone *bone, const Color &color);

	void callback(spine::AnimationState *state, spine::EventType type, spine::TrackEntry *entry, spine::Event *event);

public:
	SpineSprite();
	~SpineSprite();

	void set_skeleton_data_res(const Ref<SpineSkeletonDataResource> &_spine_skeleton_data_resource);

	Ref<SpineSkeletonDataResource> get_skeleton_data_res();

	Ref<SpineSkeleton> get_skeleton();

	Ref<SpineAnimationState> get_animation_state();

	void on_skeleton_data_changed();

	void update_skeleton(float delta);

	Transform2D get_global_bone_transform(const String &bone_name);

	void set_global_bone_transform(const String &bone_name, Transform2D transform);

	SpineConstant::UpdateMode get_update_mode();

	void set_update_mode(SpineConstant::UpdateMode v);

	Ref<SpineSkin> new_skin(const String &name);

	Ref<Material> get_normal_material();

	void set_normal_material(Ref<Material> material);

	Ref<Material> get_additive_material();

	void set_additive_material(Ref<Material> material);

	Ref<Material> get_multiply_material();

	void set_multiply_material(Ref<Material> material);

	Ref<Material> get_screen_material();

	void set_screen_material(Ref<Material> material);

	bool get_debug_bones() { return debug_bones; }

	void set_debug_bones(bool bones) { debug_bones = bones; }

	Color get_debug_bones_color() { return debug_bones_color; }

	void set_debug_bones_color(const Color &color) { debug_bones_color = color; }

	float get_debug_bones_thickness() { return debug_bones_thickness; }

	void set_debug_bones_thickness(float thickness) { debug_bones_thickness = thickness; }

	bool get_debug_regions() { return debug_regions; }

	void set_debug_regions(bool regions) { debug_regions = regions; }

	Color get_debug_regions_color() { return debug_regions_color; }

	void set_debug_regions_color(const Color &color) { debug_regions_color = color; }

	bool get_debug_meshes() { return debug_meshes; }

	void set_debug_meshes(bool meshes) { debug_meshes = meshes; }

	Color get_debug_meshes_color() { return debug_meshes_color; }

	void set_debug_meshes_color(const Color &color) { debug_meshes_color = color; }

	bool get_debug_paths() { return debug_paths; }

	void set_debug_paths(bool paths) { debug_paths = paths; }

	Color get_debug_paths_color() { return debug_paths_color; }

	void set_debug_paths_color(const Color &color) { debug_paths_color = color; }

	bool get_debug_bounding_boxes() { return debug_bounding_boxes; }

	void set_debug_bounding_boxes(bool paths) { debug_bounding_boxes = paths; }

	Color get_debug_bounding_boxes_color() { return debug_bounding_boxes_color; }

	void set_debug_bounding_boxes_color(const Color &color) { debug_bounding_boxes_color = color; }

	bool get_debug_clipping() { return debug_clipping; }

	void set_debug_clipping(bool clipping) { debug_clipping = clipping; }

	Color get_debug_clipping_color() { return debug_clipping_color; }

	void set_debug_clipping_color(const Color &color) { debug_clipping_color = color; }

#ifdef TOOLS_ENABLED
	virtual Rect2 _edit_get_rect() const;
	virtual bool _edit_use_rect() const;
#endif
};
