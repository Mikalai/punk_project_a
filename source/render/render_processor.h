#ifndef _H_PUNK_RENDER_PROCESSOR
#define _H_PUNK_RENDER_PROCESSOR

#include <config.h>
#include <scene/igraph_processor.h>

PUNK_ENGINE_BEGIN
namespace Render {
	class RenderProcessor : public Scene::IGraphProcessor {
	public:
		///
		/// \brief Initialize
		/// \param graph
		/// Common graph processor stuff
		///
		void SetGraph(ISceneGraph* graph) override;

		///
		/// \brief BeginUpdate
		/// \param dt_ms
		/// Control internal processing thread
		///
		void BeginUpdate(int dt_ms) override;
		void FinishUpdate() override;
		void WaitUpdateStart() override;
		void WaitUpdateFinish() override;

		///
		/// \brief StartProcessing
		/// Control processor state
		///
		void StartProcessing() override;
		void StopProcessing() override;
		void WaitProcessingComplete() override;

		void Destroy() override;
	private:
	};
}