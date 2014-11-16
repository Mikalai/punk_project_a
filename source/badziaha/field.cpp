#include "field.h"

void FieldCell::addEntity(Spatial* value) {
	auto it = std::find(entities.begin(), entities.end(), value);
	if (it != entities.end())
		return;
	entities.push_back(value);
}

void FieldCell::removeEntity(Spatial* value) {
	auto it = std::find(entities.begin(), entities.end(), value);
	if (it == entities.end())
		return;
	entities.erase(it);
}

//
//void GlobalField::pathFinderFunc(GlobalField* _this) {
//	GlobalField* field = _this;
//
//	while (!field->m_terminate) {
//		std::unique_lock<std::mutex> lock{ field->m_path_find_mutex };
//		auto tasks = field->m_path_find_tasks;
//		//qDebug("Recieved %d tasls", tasks.size());
//		field->m_path_find_tasks.clear();
//		lock.unlock();
//		while (!tasks.empty()) {
//			auto task = tasks.back();
//			//qDebug("Find path task recieved from %d;%d to %d;%d", task->start.x(), task->start.y(), task->end.x(), task->end.y());
//			tasks.pop_back();
//			task->has_path = field->getPath(task->start, task->end, task->path);
//			task->has_result = true;
//		}
//
//
//		lock.lock();
//		field->m_path_find_cond.wait(lock, [&field]() {
//
//			//	if terminate request - stop waiting
//			if (field->m_terminate)
//				return true;
//			//if (field->m_path_find_tasks.empty())
//			//qDebug("Wait till new find path tasks");
//			return !field->m_path_find_tasks.empty();
//		});
//	}
//}
