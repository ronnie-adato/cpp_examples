# Problem Description

## Handler/Message Design

This module demonstrates a polymorphic handler/message pattern in C++:

- `Handler1` and `Handler2` classes.
- Both handlers process `Message1` in the same way (shared logic).
- `Message2` is handled differently by each handler (custom logic per handler).
- Only `Handler2` handles `Message3`; `Handler1` does not process this message type.

This design allows flexible and type-safe message dispatch, with clear separation of shared and specialized behavior.
