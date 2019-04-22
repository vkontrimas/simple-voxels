#pragma once
#ifndef SIVOX_GAME_CHUNKPROCESSOR_HPP
#define SIVOX_GAME_CHUNKPROCESSOR_HPP

#include "common.hpp"

namespace sivox {
    /*
     * Processes chunks as they are created, loaded, generated, updated, unloaded and
     * destroyed. Any chunk can be in one of a number of states at any given time:
     *   - Created
     *     The chunk has just been created and contaisn no meaningful block data. The data
     *     must now be loaded or generated.
     *
     *   - Updated
     *     The chunk has just been modified and its mesh must be recomputed. (Possibly
     *     along with other data...)
     *
     *   - Loaded
     *     The chunk has been loaded or generated and contains actual terrain data. This
     *     is the resting state most chunks are going to be in.
     *
     *   - Unloaded
     *     The chunk contains actual data but is no longer loaded. Its data can be saved
     *     to disk at this point.
     *
     *   - Unused
     *     The chunk is not in use and may be freed or reused. While it may contain
     *     meaningful data, it's best to assume it contains garbage.
     *
     *  The ChunkProcessor contains a queue of chunk pointers. Chunks may be added to the
     *  queue as needed and will be processed one by one, moving them from one state to
     *  the next using whatever method is necessary.
     *
     *  The state transitions are as follows:
     *   - Created --> Updated
     *     The chunk is loaded from disk or generated. Its mesh must be generated for
     *     display and other data may be computed too.
     *
     *   - Loaded --> Loaded
     *     Currently chunks in the loaded state should not be submitted at all. So a
     *     Loaded chunk is simply skipped. (In practice, we check if a chunk is Loaded
     *     before even adding it to the queue to save effort.)
     *
     *     IDEA: In the future, we may implement this transition to simulate fluids or do
     *     other dynamic things. (Though a 'Loaded --> Updated' transition probably makes
     *     more sense...)
     *
     *   - Unloaded --> Unused
     *     The data of an unloaded chunk may be saved to disk before its state is updated.
     *     As this is currently not needed, we will simply change the state immediately
     *     instead of adding the chunk to the queue.
     *
     *  Any other state transitions are up to the user and must happen elsewhere. Reusing
     *  an Unused chunk will require the state to be manually set to Created. Same for
     *  freeing it. Changing the state from Loaded to Updated when a block is changed is
     *  also up to the user, meant to be done wherever the block placement logic is
     *  handled.
     *
     *  Internally the ChunkProcessor is intended to use a lockfree thread pool to
     *  accomplish the transitions since they can lock up the thread for a while.
     *  (Recomputing a mesh can be costly, disk IO operations can block for a while, ...)
     */
    class ChunkProcessor {

    };
}
#endif // SIVOX_GAME_CHUNKPROCESSOR_HPP
