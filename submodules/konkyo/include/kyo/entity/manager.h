
#pragma once

#include "kyo/entity/composite.h"


class EntityManager: private CompositeEntity {
public:

    EntityManager() {

        this->set_name("Element");
    }


    using CompositeEntity::Element;
    using CompositeEntity::Drawable;
    using CompositeEntity::spawn_entity;
    using CompositeEntity::delete_entity;
    using CompositeEntity::draw;
    using CompositeEntity::Drawable::draw;
    using CompositeEntity::on_tick;
	using CompositeEntity::on_lerp;
    using CompositeEntity::entity_count;
    using CompositeEntity::entity_count_rec;
};
