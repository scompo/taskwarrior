use super::Timestamp;

/// An annotation for a task
#[derive(Debug, PartialEq)]
pub struct Annotation {
    /// Time the annotation was made
    pub entry: Timestamp,
    /// Content of the annotation
    pub description: String,
}
