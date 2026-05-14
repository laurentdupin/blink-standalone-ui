#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_TREE_BRIDGE_PROBE_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_TREE_BRIDGE_PROBE_H_

namespace blink::standalone_renderer_probe {

void ResetStandaloneHTMLTreeBuilderRecordingForStandaloneRenderer();
int StandaloneHTMLTreeBuilderRecordedNodeCountForStandaloneRenderer();
int StandaloneHTMLTreeBuilderRecordedParentAtForStandaloneRenderer(int index);
int StandaloneHTMLTreeBuilderRecordedDepthAtForStandaloneRenderer(int index);
int StandaloneHTMLTreeBuilderRecordedFirstChildAtForStandaloneRenderer(
    int index);
int StandaloneHTMLTreeBuilderRecordedChildCountAtForStandaloneRenderer(
    int index);
void StandaloneHTMLTreeBuilderRecordedNodeKindAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
void StandaloneHTMLTreeBuilderRecordedNodeNameAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
void StandaloneHTMLTreeBuilderRecordedNodeValueAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
int StandaloneHTMLTreeBuilderRecordedNextSiblingAtForStandaloneRenderer(
    int index);
int StandaloneHTMLTreeBuilderDOMLinkedNodeCountForStandaloneRenderer();
int StandaloneHTMLTreeBuilderDOMLinkedMaxDepthForStandaloneRenderer();
int StandaloneHTMLTreeBuilderDOMSnapshotNodeCountForStandaloneRenderer();
int StandaloneHTMLTreeBuilderDOMSnapshotParentAtForStandaloneRenderer(
    int index);
int StandaloneHTMLTreeBuilderDOMSnapshotDepthAtForStandaloneRenderer(int index);
int StandaloneHTMLTreeBuilderDOMSnapshotFirstChildAtForStandaloneRenderer(
    int index);
int StandaloneHTMLTreeBuilderDOMSnapshotNextSiblingAtForStandaloneRenderer(
    int index);
int StandaloneHTMLTreeBuilderDOMSnapshotChildCountAtForStandaloneRenderer(
    int index);
void StandaloneHTMLTreeBuilderDOMSnapshotNodeKindAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
void StandaloneHTMLTreeBuilderDOMSnapshotNodeNameAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
void StandaloneHTMLTreeBuilderDOMSnapshotNodeValueAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
int StandaloneHTMLTreeBuilderLayoutSnapshotBoxCountForStandaloneRenderer();
int StandaloneHTMLTreeBuilderLayoutSnapshotNodeAtForStandaloneRenderer(
    int index);
float StandaloneHTMLTreeBuilderLayoutSnapshotXAtForStandaloneRenderer(
    int index);
float StandaloneHTMLTreeBuilderLayoutSnapshotYAtForStandaloneRenderer(
    int index);
float StandaloneHTMLTreeBuilderLayoutSnapshotWidthAtForStandaloneRenderer(
    int index);
float StandaloneHTMLTreeBuilderLayoutSnapshotHeightAtForStandaloneRenderer(
    int index);
void StandaloneHTMLTreeBuilderLayoutSnapshotRoleAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
int StandaloneHTMLTreeBuilderPaintArtifactChunkCountForStandaloneRenderer();
int StandaloneHTMLTreeBuilderPaintArtifactChunkNodeAtForStandaloneRenderer(
    int index);
float StandaloneHTMLTreeBuilderPaintArtifactChunkXAtForStandaloneRenderer(
    int index);
float StandaloneHTMLTreeBuilderPaintArtifactChunkYAtForStandaloneRenderer(
    int index);
float StandaloneHTMLTreeBuilderPaintArtifactChunkWidthAtForStandaloneRenderer(
    int index);
float StandaloneHTMLTreeBuilderPaintArtifactChunkHeightAtForStandaloneRenderer(
    int index);
void StandaloneHTMLTreeBuilderPaintArtifactChunkIdAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
void StandaloneHTMLTreeBuilderPaintArtifactChunkRoleAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
void StandaloneHTMLTreeBuilderPaintArtifactChunkOpAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity);
int StandaloneBlinkPlatformPaintArtifactTypesReachableForStandaloneRenderer();
int StandaloneBlinkRealPaintBridgeSurfaceReachableForStandaloneRenderer();
int StandaloneBlinkRealPaintBridgeRequiresPaintCleanForStandaloneRenderer();

// Temporary smoke entry point until a real Blink Document/HTMLDocumentParser is
// wired to drive HTMLTreeBuilder::ConstructTree() in this reduced target.
void StandaloneHTMLTreeBuilderRecordSmokeInsertionForStandaloneRenderer();
void StandaloneHTMLTreeBuilderParseHTMLForStandaloneRenderer(const char* html);

}  // namespace blink::standalone_renderer_probe

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_TREE_BRIDGE_PROBE_H_
