// Generated for the standalone Blink renderer cut.
// Source mapping: third_party/blink/public/blink_resources.grd
// This embeds Blink UA stylesheet resources without Chromium pak/network services.

#include "third_party/blink/public/resources/grit/blink_resources.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

#include <string_view>

namespace blink {
namespace {

// IDR_UASTYLE_HTML_CSS: third_party/blink/renderer/core/html/resources/html.css
constexpr char kResource0[] = R"BlinkUA(
/*
 * The default style sheet used to render HTML.
 *
 * Copyright (C) 2000 Lars Knoll (knoll@kde.org)
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

@namespace "http://www.w3.org/1999/xhtml";

html {
    display: block;
}

:root {
    view-transition-name: root;
}

:active-view-transition {
    view-transition-name: root;
}

:active-view-transition:not(:root) {
  view-transition-group: contain;
}

@keyframes -ua-view-transition-fade-in {
  from { opacity: 0; }
}

@keyframes -ua-view-transition-fade-out {
  to { opacity: 0; }
}

@keyframes -ua-mix-blend-mode-plus-lighter {
  from { mix-blend-mode: plus-lighter }
  to { mix-blend-mode: plus-lighter }
}

/* generic block-level elements */

body {
    display: block;
    margin: 8px;
}

body:-webkit-full-page-media {
    background-color: rgb(0, 0, 0)
}

p {
    display: block;
    margin-block-start: 1__qem;
    margin-block-end: 1__qem;
    margin-inline-start: 0;
    margin-inline-end: 0;
}

div {
    display: block
}

article, aside, footer, header, hgroup, main, nav, search, section {
    display: block
}

marquee {
    display: inline-block;
    width: -webkit-fill-available;
}

address {
    display: block
}

blockquote {
    display: block;
    margin-block-start: 1__qem;
    margin-block-end: 1em;
    margin-inline-start: 40px;
    margin-inline-end: 40px;
}

figcaption {
    display: block
}

figure {
    display: block;
    margin-block-start: 1em;
    margin-block-end: 1em;
    margin-inline-start: 40px;
    margin-inline-end: 40px;
}

q {
    display: inline
}

q:before {
    content: open-quote;
}

q:after {
    content: close-quote;
}

center {
    display: block;
    /* special centering to be able to emulate the html4/netscape behaviour */
    text-align: -webkit-center
}

hr {
    display: block;
    overflow: hidden;
    margin-block-start: 0.5em;
    margin-block-end: 0.5em;
    margin-inline-start: auto;
    margin-inline-end: auto;
    border-style: inset;
    border-width: 1px;
    color: gray;
}

map {
    display: inline
}

video {
    object-fit: contain;
}

video:-webkit-full-page-media {
    margin: auto;
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    max-height: 100%;
    max-width: 100%;
}

audio:not([controls]) {
  display: none !important;
}

/** TODO(crbug.com/985623): Remove these hard-coded audio tag size.
 * This fixed audio tag width/height leads to fail the wpt tests below.
 * crbug.com/955170 external/wpt/css/css-contain/contain-size-replaced-003a.html
 * crbug.com/955163 external/wpt/css/css-contain/contain-size-replaced-003b.html
 * crbug.com/955163 external/wpt/css/css-contain/contain-size-replaced-003c.html
 */
audio {
  width: 300px;
  height: 54px;
}

video, canvas, img {
  overflow: clip;
  overflow-clip-margin: content-box;
}

iframe, embed, object, fencedframe {
   overflow: clip !important;
   overflow-clip-margin: content-box !important;
}

/* heading elements */

h1 {
    display: block;
    font-size: 2em;
    margin-block-start: 0.67__qem;
    margin-block-end: 0.67em;
    margin-inline-start: 0;
    margin-inline-end: 0;
    font-weight: bold
}

h2 {
    display: block;
    font-size: 1.5em;
    margin-block-start: 0.83__qem;
    margin-block-end: 0.83em;
    margin-inline-start: 0;
    margin-inline-end: 0;
    font-weight: bold
}

h3 {
    display: block;
    font-size: 1.17em;
    margin-block-start: 1__qem;
    margin-block-end: 1em;
    margin-inline-start: 0;
    margin-inline-end: 0;
    font-weight: bold
}

h4 {
    display: block;
    margin-block-start: 1.33__qem;
    margin-block-end: 1.33em;
    margin-inline-start: 0;
    margin-inline-end: 0;
    font-weight: bold
}

h5 {
    display: block;
    font-size: .83em;
    margin-block-start: 1.67__qem;
    margin-block-end: 1.67em;
    margin-inline-start: 0;
    margin-inline-end: 0;
    font-weight: bold
}

h6 {
    display: block;
    font-size: .67em;
    margin-block-start: 2.33__qem;
    margin-block-end: 2.33em;
    margin-inline-start: 0;
    margin-inline-end: 0;
    font-weight: bold
}

/* tables */

table {
    display: table;
    box-sizing: border-box;
    border-spacing: 2px;
    border-collapse: separate;
    text-indent: initial;
    @supports not blink-feature(TableDefaultBorderColorCurrentColor) {
        border-color: gray;
    }
}

thead {
    display: table-header-group;
    vertical-align: middle;
    border-color: inherit
}

tbody {
    display: table-row-group;
    vertical-align: middle;
    border-color: inherit
}

tfoot {
    display: table-footer-group;
    vertical-align: middle;
    border-color: inherit
}

/* for tables without table section elements (can happen with XHTML or dynamically created tables) */
table > tr {
    vertical-align: middle;
}

col {
    display: table-column
}

colgroup {
    display: table-column-group
}

tr {
    display: table-row;
    vertical-align: inherit;
    border-color: inherit
}

td, th {
    display: table-cell;
    vertical-align: inherit;
}

/* When the td/th are inside a table (the normal case), the padding is taken
   care of by HTMLTableCellElement::AdditionalPresentationAttributeStyle(). */
td:not(table td),
th:not(table th) {
  padding: 1px;
}

th {
    font-weight: bold;
    text-align: -internal-center
}

caption {
    display: table-caption;
    text-align: -webkit-center
}

/* lists */

ul, menu, dir {
    display: block;
    list-style-type: disc;
    margin-block-start: 1__qem;
    margin-block-end: 1em;
    padding-inline-start: 40px
}

ol {
    display: block;
    list-style-type: decimal;
    margin-block-start: 1__qem;
    margin-block-end: 1em;
    padding-inline-start: 40px
}

li {
    display: list-item;
    text-align: match-parent;
}

:is(dir, dl, menu, ol, ul) dir,
:is(dir, dl, menu, ol, ul) dl,
:is(dir, dl, menu, ol, ul) menu,
:is(dir, dl, menu, ol, ul) ol,
:is(dir, dl, menu, ol, ul) ul {
    margin-block-start: 0;
    margin-block-end: 0;
}

:is(dir, menu, ol, ul) dir,
:is(dir, menu, ol, ul) menu,
:is(dir, menu, ol, ul) ul {
    list-style-type: circle
}

:is(dir, menu, ol, ul) :is(dir, menu, ol, ul) dir,
:is(dir, menu, ol, ul) :is(dir, menu, ol, ul) menu,
:is(dir, menu, ol, ul) :is(dir, menu, ol, ul) ul {
    list-style-type: square
}

/* TODO(crbug.com/40774317, crbug.com/354025385): We should add rule
   ol, ul, menu { counter-reset: list-item; }
   once it is supported. */

dd {
    display: block;
    margin-inline-start: 40px
}

dl {
    display: block;
    margin-block-start: 1__qem;
    margin-block-end: 1em;
}

dt {
    display: block
}

/* form elements */

form {
    display: block;
    margin-top: 0__qem;
}

:-webkit-any(table, thead, tbody, tfoot, tr) > form:-internal-is-html {
  display: none !important;
}

label {
    cursor: default;
}

fieldset {
    display: block;
    margin-inline: 2px;
    border: groove 2px ThreeDFace;
    padding-block: 0.35em 0.625em;
    padding-inline: 0.75em;
    min-inline-size: min-content;
}

legend {
    display: block;
    padding-inline: 2px;
}

legend[align=left i] {
    justify-self: left;
}

legend[align=center i] {
    justify-self: center;
}

legend[align=right i] {
    justify-self: right;
}

button {
    appearance: auto;
    -internal-align-content-block: center;
}

input, textarea, select, button {
    margin: 0__qem;
    font: -webkit-small-control;
    text-rendering: auto; /* FIXME: Remove when tabs work with optimizeLegibility. */
    color: FieldText;
    letter-spacing: normal;
    word-spacing: normal;
    line-height: normal;
    text-transform: none;
    text-indent: 0;
    text-shadow: none;
    display: inline-block;
    text-align: start;
}
@supports blink-feature(AppearanceBase) {
  /* TODO(crbug.com/450139531): Merge these styles with the above block when
   * these styles can apply to textarea, select, and button as well. */
  input {
    margin: -internal-auto-base(0__qem, unset);
    /* FIXME: Remove text-rendering:auto when tabs work with optimizeLegibility. */
    text-rendering: -internal-auto-base(auto, unset);
    letter-spacing: -internal-auto-base(normal, unset);
    word-spacing: -internal-auto-base(normal, unset);
    line-height: -internal-auto-base(normal, unset);
    text-shadow: -internal-auto-base(none, unset);
    /* text-transform, text-indent, and text-align are supposed to be set to
     * initial. Since the auto appearance is also using the initial values, we
     * don't need to use -internal-auto-base() on them. */
  }

  input, textarea, button {
    color: -internal-auto-base(FieldText, inherit);
    font: -internal-auto-base(-webkit-small-control, inherit);
  }
}

textarea {
    appearance: auto;
    column-count: initial !important;
    -webkit-rtl-ordering: logical;
    cursor: text;
    white-space: pre-wrap;
    word-wrap: break-word;
    font-family: monospace;

    @supports not blink-feature(AppearanceBase) {
        border: 1px solid light-dark(#767676, #858585);
        background-color: Field;
        resize: -internal-textarea-auto;
        padding: 2px;
    }

    @supports blink-feature(AppearanceBase) {
        border: 1px solid -internal-auto-base(light-dark(#767676, #858585), currentColor);
        background-color: -internal-auto-base(Field, transparent);
        resize: -internal-auto-base(-internal-textarea-auto, none);
        padding: -internal-auto-base(2px, unset);
        box-sizing: -internal-auto-base(content-box, border-box);
    }
}

input {
    appearance: auto;
    cursor: text;
    @supports blink-feature(AppearanceBase) {
        padding: -internal-auto-base(1px 0, unset);
        border: -internal-auto-base(2px inset light-dark(#767676, #858585), 1px solid);
        -webkit-rtl-ordering: -internal-auto-base(logical, unset);
        background-color: -internal-auto-base(Field, transparent);
        box-sizing: -internal-auto-base(content-box, border-box);
    }
    @supports not blink-feature(AppearanceBase) {
        padding: 1px 0;
        border: 2px inset light-dark(#767676, #858585);
        -webkit-rtl-ordering: logical;
        background-color: Field;
    }
}

input:not([type="file" i], [type="image" i], [type="checkbox" i], [type="radio" i]) {
    -internal-align-content-block: center;
}

input[type="search" i] {
    appearance: auto;
    box-sizing: border-box;
}

input::-webkit-textfield-decoration-container {
    display: flex !important;
    align-items: center;
    -webkit-user-modify: read-only !important;
    content: none !important;
    writing-mode: inherit !important;
}

@supports not blink-feature(HTMLInputElementDropWebkitClearButton) {
    input::-webkit-clear-button {
        appearance: auto;
        display: inline-block;
        cursor: default;
        flex: none;
        -webkit-user-modify: read-only !important;
        margin-inline-start: 2px;
        opacity: 0;
        pointer-events: none;
    }

    input:enabled:read-write:-webkit-any(:focus,:hover)::-webkit-clear-button {
        opacity: 1;
        pointer-events: auto;
    }
}

input[type="search" i]::-webkit-search-cancel-button {
    appearance: auto;
    display: block;
    cursor: default;
    flex: none;
    -webkit-user-modify: read-only !important;
    margin-inline-start: 1px;
    margin-inline-end: 3px;
    opacity: 0;
    pointer-events: none;
    user-select: none !important;

    @supports blink-feature(AppearanceBase) {
        /** This pseudo element doesn't exist in the standard layout. */
        display: -internal-auto-base(revert-rule, none) !important;
    }
}

input[type="search" i]:enabled:read-write:-webkit-any(:focus,:hover)::-webkit-search-cancel-button {
    opacity: 1;
    pointer-events: auto;
}

/* Specifying all of the type attributes in the selector below does not seem
 * necessary and causes a performance issue when combined with
 * -internal-auto-base(), so the AppearanceBase one does not include the type
 * attribute selectors. */
@supports not blink-feature(AppearanceBase) {
  input,
  input[type="email" i],
  input[type="number" i],
  input[type="password" i],
  input[type="search" i],
  input[type="tel" i],
  input[type="text" i],
  input[type="url" i] {
    padding-block: 1px;
    padding-inline: 2px;
  }
}
@supports blink-feature(AppearanceBase) {
  input {
    padding-block: -internal-auto-base(1px, unset);
    padding-inline: -internal-auto-base(2px, unset);
  }
}

input[type="tel" i] {
  direction: ltr;
}

input::-webkit-inner-spin-button {
    appearance: auto;
    display: inline-block;
    cursor: default;
    flex: none;
    align-self: stretch;
    -webkit-user-modify: read-only !important;
    opacity: 0;
    pointer-events: none;

    @supports blink-feature(AppearanceBase) {
        /** This pseudo element doesn't exist in the standard layout. */
        display: -internal-auto-base(revert-rule, none) !important;
    }
}

input:enabled:read-write:-webkit-any(:focus,:hover)::-webkit-inner-spin-button {
    opacity: 1;
    pointer-events: auto;
}

::-webkit-input-placeholder {
    -webkit-text-security: none;
    color: #757575;
    direction: inherit !important;
    pointer-events: none !important;
    text-orientation: inherit !important;
    writing-mode: inherit !important;
}

input::-webkit-input-placeholder {
    text-overflow: inherit;
    line-height: initial !important;
    white-space: pre;
    word-wrap: normal;
    overflow: hidden;
    -webkit-user-modify: read-only !important;
}

input::-internal-input-suggested {
    text-overflow: inherit;
    white-space: nowrap;
    overflow: hidden;
}

input::-internal-input-suggested,
textarea::-internal-input-suggested {
    font: -webkit-small-control !important;
    /* -webkit-small-control does not pin the font-feature-settings and we want
       previews to look consistent. */
    font-feature-settings: normal !important;
    /* Prevent that overflow affects the scrollable area. Without this,
       LayoutBox::*Scroll{Height,Width}() may determine the scroll width/height
       from the scrollable area instead of from the overrides in
       LayoutTextControl{Single,Multi}Line::Scroll{Height,Width}(). */
    overflow: hidden !important;
    overflow-anchor: none;
}

textarea::-internal-input-suggested {
  font-family: monospace !important;
}

input[type="password" i] {
    -webkit-text-security: disc !important;
}

input[type="password" i]::-internal-input-suggested:not(.reveal-password) {
    -webkit-text-security: disc !important;
}

input[type="password" i]::-internal-input-suggested.reveal-password {
    -webkit-text-security: none;
}

input[type="password" i]::-internal-reveal {
  width: 1.3em;
  height: 1.3em;
  cursor: default;
  flex: none;
  background-image: url(images/password_reveal_on.svg);
  background-repeat: no-repeat;
  background-position: center;
  background-size: contain;
  margin-left: 3px;
  margin-right: 3px;
}

input[type="password" i]::-internal-reveal.reveal {
  background-image: url(images/password_reveal_off.svg);
}

input[type="password" i]::-internal-reveal:hover,
input[type="password" i]::-internal-reveal:focus {
  border-radius: 1px;
  cursor: pointer;
}

input[type="hidden" i], input[type="image" i], input[type="file" i] {
    appearance: none;
    padding: initial;
    background-color: initial;
    border: initial;
    cursor: default;
}

input[type="file" i] {
    align-items: baseline;
    color: inherit;
    text-align: start !important;
    /* Prevent a malicious author from using a custom string for text-overflow
       to spoof a filename. */
    text-overflow: ellipsis !important;
    white-space: pre;
}

input[type="image" i] {
    cursor: pointer;
}

input[type="radio" i],
input[type="checkbox" i] {
    @supports not blink-feature(AppearanceBase) {
        padding: initial;
        background-color: initial;
        border: initial;
        cursor: default;
    }
    @supports blink-feature(AppearanceBase) {
        padding: -internal-auto-base(initial, unset);
        background-color: -internal-auto-base(initial, transparent);
        border: -internal-auto-base(initial, 1px solid currentColor);
        cursor: -internal-auto-base(default, unset);

        block-size: -internal-auto-base(unset, 1em);
        inline-size: -internal-auto-base(unset, 1em);
        font-size: -internal-auto-base(unset, max(1em, 24px));
        display: -internal-auto-base(inline-block, inline-flex);
        align-items: -internal-auto-base(unset, center);
        justify-content: -internal-auto-base(unset, center);
    }
}

input[type="checkbox" i] {
    @supports not blink-feature(AppearanceBase) {
        margin: 3px 3px 3px 4px;
    }
    @supports blink-feature(AppearanceBase) {
        margin: -internal-auto-base(3px 3px 3px 4px, unset);
    }
}

input[type="radio" i] {
    @supports not blink-feature(AppearanceBase) {
        margin:3px 3px 0 5px;
    }
    @supports blink-feature(AppearanceBase) {
        margin: -internal-auto-base(3px 3px 0 5px, unset);
        border-radius: -internal-auto-base(unset, 50%);
        padding: -internal-auto-base(initial, 0.15em);
    }
}

@supports blink-feature(AppearanceBase) {
    input[type="checkbox" i]::checkmark {
        content: -internal-auto-base(unset, '\2713' / '');
    }

    input[type="radio" i]::checkmark  {
        content: -internal-auto-base(unset, '');
    }

    input[type="checkbox" i]:not(:checked, :indeterminate)::checkmark,
    input[type="radio" i]:not(:checked)::checkmark {
        visibility: hidden;
    }

    input[type="checkbox" i]:indeterminate::checkmark {
        content: -internal-auto-base(unset, '\2500' / '');
    }

    input[type="radio" i]:checked::checkmark {
        background-color: currentColor;
        display: inline-block;
        border-radius: inherit;
        height: 100%;
        width: 100%;
    }
}

input[type="button" i], input[type="submit" i], input[type="reset" i] {
    -internal-empty-line-height: fabricated;
    appearance: auto;
    user-select: none;
    white-space: pre
}

input[type="file" i]::-webkit-file-upload-button {
    appearance: auto;
    -webkit-user-modify: read-only !important;
    white-space: nowrap;
    margin: 0;
    margin-inline-end: 4px; /* See FileUploadControlIntrinsicInlineSize() */
    font-size: inherit;
}

input[type="button" i],
input[type="submit" i],
input[type="reset" i],
input[type="file" i]::-webkit-file-upload-button,
button {
    cursor: default;
    box-sizing: border-box;

    @supports not blink-feature(AppearanceBase) {
        text-align: center;
        cursor: default;
        padding-block: 1px;
        padding-inline: 6px;
        border: 2px outset ButtonBorder;
        background-color: ButtonFace;
        color: ButtonText;
    }

    @supports blink-feature(AppearanceBase) {
        color: -internal-auto-base(ButtonText, inherit);
        background-color: -internal-auto-base(ButtonFace, transparent);
        border: -internal-auto-base(2px outset ButtonBorder, 1px solid currentColor);

        padding-block: -internal-auto-base(1px, 0.25em);
        padding-inline: -internal-auto-base(6px, 0.5em);
        border-radius: -internal-auto-base(unset, 0.5em);
        min-block-size: -internal-auto-base(unset, calc-size(auto, max(size, 24px, 1lh)));
        max-inline-size: -internal-auto-base(unset, calc-size(auto, max(size, 24px)));

        display: -internal-auto-base(revert-rule, inline-flex);
        gap: -internal-auto-base(unset, 0.5em);

        user-select: -internal-auto-base(revert-rule, none);

        text-align: -internal-auto-base(center, initial);
    }
}

input[type="checkbox" i]:disabled,
input[type="file" i]:disabled,
input[type="hidden" i]:disabled,
input[type="image" i]:disabled,
input[type="radio" i]:disabled,
input[type="range" i]:disabled {
    background-color: initial;
}

input[type="range" i] {
    appearance: auto;
    padding: initial;
    border: initial;
    margin: 2px;
    cursor: default;
    color: light-dark(#101010, #ffffff);
}

input[type="range" i]::-webkit-slider-container,
input[type="range" i]::-webkit-media-slider-container {
    appearance: inherit;
    flex: 1;
    min-inline-size: 0;
    box-sizing: border-box;
    -webkit-user-modify: read-only !important;
    display: flex;
}

input[type="range" i]:-internal-has-datalist::-webkit-slider-container {
    /*
     * See LayoutThemeDefault. "22px" is
     * 2 * (SliderTickOffsetFromTrackCenter() + SliderTickSize().Height()).
     */
    min-block-size: 22px;
}

input[type="range" i]::-webkit-slider-runnable-track {
    flex: 1;
    min-inline-size: 0;
    align-self: center;

    box-sizing: border-box;
    -webkit-user-modify: read-only !important;
    display: block;
}

input[type="range" i]::-webkit-slider-thumb,
input[type="range" i]::-webkit-media-slider-thumb {
    appearance: auto;
    box-sizing: border-box;
    -webkit-user-modify: read-only !important;
    display: block;
}

input[type="range" i]:disabled {
  color: #c5c5c5;
}

input[type="button" i]:disabled,
input[type="submit" i]:disabled,
input[type="reset" i]:disabled,
input[type="file" i]:disabled::-webkit-file-upload-button,
button:disabled {
    @supports not blink-feature(AppearanceBase) {
        background-color: light-dark(rgba(239, 239, 239, 0.3), rgba(19, 1, 1, 0.3));
        border-color: light-dark(rgba(118, 118, 118, 0.3), rgba(195, 195, 195, 0.3));
        color: light-dark(rgba(16, 16, 16, 0.3), rgba(255, 255, 255, 0.3));
    }

    @supports blink-feature(AppearanceBase) {
        background-color: -internal-auto-base(light-dark(rgba(239, 239, 239, 0.3), rgba(19, 1, 1, 0.3)), revert-rule);
        border-color: -internal-auto-base(light-dark(rgba(118, 118, 118, 0.3), rgba(195, 195, 195, 0.3)), revert-rule);
        color: -internal-auto-base(light-dark(rgba(16, 16, 16, 0.3), rgba(255, 255, 255, 0.3)), color-mix(currentColor 50%, transparent));
    }
}

input[type="color" i]:disabled {
    @supports blink-feature(AppearanceBase) {
        background-color: -internal-auto-base(light-dark(rgba(239, 239, 239, 0.3), rgba(19, 1, 1, 0.3)), transparent);
        border-color: -internal-auto-base(light-dark(rgba(118, 118, 118, 0.3), rgba(195, 195, 195, 0.3)), currentColor);
        color: -internal-auto-base(light-dark(rgba(16, 16, 16, 0.3), rgba(255, 255, 255, 0.3)), color-mix(currentColor 50%, transparent));
    }
    @supports not blink-feature(AppearanceBase) {
        background-color: light-dark(rgba(239, 239, 239, 0.3), rgba(19, 1, 1, 0.3));
        border-color: light-dark(rgba(118, 118, 118, 0.3), rgba(195, 195, 195, 0.3));
        color: light-dark(rgba(16, 16, 16, 0.3), rgba(255, 255, 255, 0.3));
    }
}

input[type="button" i]:active, input[type="submit" i]:active, input[type="reset" i]:active, input[type="file" i]:active::-webkit-file-upload-button, button:active {
    @supports not blink-feature(AppearanceBase) {
        border-style: inset;
    }
    @supports blink-feature(AppearanceBase) {
        border-style: -internal-auto-base(inset, revert-rule);
    }
}

input[type="button" i]:active:disabled, input[type="submit" i]:active:disabled, input[type="reset" i]:active:disabled, input[type="file" i]:active:disabled::-webkit-file-upload-button, button:active:disabled {
    @supports not blink-feature(AppearanceBase) {
        border-style: outset;
    }
    @supports blink-feature(AppearanceBase) {
        border-style: -internal-auto-base(outset, revert-rule);
    }
}

input:disabled, textarea:disabled {
    cursor: default;

    @supports not blink-feature(AppearanceBase) {
        background-color: light-dark(rgba(239, 239, 239, 0.3), rgba(59, 59, 59, 0.3));
        color: light-dark(#545454, #aaaaaa);
    }

    @supports blink-feature(AppearanceBase) {
        background-color: -internal-auto-base(light-dark(rgba(239, 239, 239, 0.3), rgba(59, 59, 59, 0.3)), unset);
        color: -internal-auto-base(light-dark(#545454, #aaaaaa), color-mix(currentColor 50%, transparent));
    }
}

option:-internal-spatial-navigation-focus {
    outline: light-dark(black, white) dashed 1px;
    outline-offset: -1px;
}

input:not([type="image" i], [type="range" i], [type="checkbox" i], [type="radio" i]) {
  overflow: clip !important;
  overflow-clip-margin: 0px !important;
}

/* https://html.spec.whatwg.org/multipage/rendering.html#hidden-elements */
/* TODO(crbug.com/1231263): <area> should be display:none. */
area {
  display: inline;
}
base, basefont, datalist, head, link, meta, noembed,
noframes, param, rp, script, style, template, title {
  display: none;
}
input[type="hidden" i] {
  display: none !important;
}

area:-webkit-any-link {
    cursor: pointer;
}

input[type="checkbox" i] {
    appearance: auto;
    box-sizing: border-box;
}

input[type="radio" i] {
    appearance: auto;
    box-sizing: border-box;
}

input[type="color" i] {
    appearance: auto;
    box-sizing: border-box;

    @supports not blink-feature(AppearanceBase) {
        inline-size: 50px;
        block-size: 27px;
        /* Same as native_theme_base. */
        border: 1px solid ButtonBorder;
        padding: 1px 2px;
        cursor: default;
        background-color: ButtonFace;
        color: ButtonText;
    }

    @supports blink-feature(AppearanceBase) {
        inline-size: -internal-auto-base(50px, auto);
        block-size: -internal-auto-base(27px, auto);
        /* Same as native_theme_base when auto. */
        border: 1px solid -internal-auto-base(ButtonBorder, currentColor);
        padding: -internal-auto-base(1px 2px, 0);
        cursor: -internal-auto-base(default, inherit);
        background-color: -internal-auto-base(ButtonFace, transparent);
        color: -internal-auto-base(ButtonText, inherit);

        min-inline-size: -internal-auto-base(unset, 24px);
        min-block-size: -internal-auto-base(unset, max(24px, 1lh));
        user-select: -internal-auto-base(unset, none);
        display: -internal-auto-base(inline-block, inline-flex);
        gap: -internal-auto-base(unset, 0.5em);
        border-radius: -internal-auto-base(unset, 0.5em);
        overflow: -internal-auto-base(revert-rule, clip);
    }
}

@supports blink-feature(AppearanceBase) {
    input[type="button" i]:enabled:hover,
    input[type="reset" i]:enabled:hover,
    input[type="submit" i]:enabled:hover,
    input[type="file" i]:enabled::-webkit-file-upload-button:hover,
    input[type="color" i]:enabled:hover,
    button:enabled:hover {
        background-color: -internal-auto-base(revert-rule, color-mix(currentColor 10%, transparent));
    }

    input[type="button" i]:enabled:active,
    input[type="reset" i]:enabled:active,
    input[type="submit" i]:enabled:active,
    input[type="file" i]:enabled::-webkit-file-upload-button:active,
    input[type="color" i]:enabled:active,
    button:enabled:active {
        background-color: -internal-auto-base(revert-rule, color-mix(currentColor 20%, transparent));
    }
}

input[type="color" i]::-webkit-color-swatch-wrapper {
    @supports blink-feature(AppearanceBase) {
        display: -internal-auto-base(flex, contents);
    }
    @supports not blink-feature(AppearanceBase) {
        display: flex;
    }

    padding: 4px 2px;
    box-sizing: border-box;
    -webkit-user-modify: read-only !important;
    width: 100%;
    height: 100%
}

input[type="color" i]::-webkit-color-swatch {
    /* The swatch should not be affected by color scheme. */
    color-scheme: only light;
    background-color: #000000;
    -webkit-user-modify: read-only !important;
    @supports not blink-feature(AppearanceBase) {
        border: 1px solid #777777;
        min-width: 0;
        flex: 1;
    }

    @supports blink-feature(AppearanceBase) {
        border: -internal-auto-base(1px solid #777777, revert-rule);
        min-width: -internal-auto-base(0, revert-rule);
        flex: -internal-auto-base(1, revert-rule);

        color: -internal-auto-base(revert-rule, inherit);
        font: -internal-auto-base(revert-rule, inherit);
        box-sizing: -internal-auto-base(revert-rule, border-box);

        inline-size: -internal-auto-base(revert-rule, stretch);
        block-size: -internal-auto-base(revert-rule, stretch);
        forced-color-adjust: -internal-auto-base(revert-rule, none);
    }
}

input::-webkit-calendar-picker-indicator {
    display: inline-block;
    inline-size: 0.66em;
    block-size: 0.66em;
    padding-block: 0.17em;
    padding-inline: 0.34em;
    -webkit-user-modify: read-only !important;
    opacity: 0;
    cursor: default;
    pointer-events: none;
}

input::-webkit-calendar-picker-indicator:hover {
    background-color: #eee;
}

input:enabled:read-write:-webkit-any(:focus,:hover)::-webkit-calendar-picker-indicator,
input::-webkit-calendar-picker-indicator:focus {
    opacity: 1;
    pointer-events: auto;
}

input[type="date" i]:disabled::-webkit-inner-spin-button,
input[type="datetime-local" i]:disabled::-webkit-inner-spin-button,
input[type="month" i]:disabled::-webkit-inner-spin-button,
input[type="week" i]:disabled::-webkit-inner-spin-button,
input:disabled::-webkit-calendar-picker-indicator,
input[type="date" i][readonly]::-webkit-inner-spin-button,
input[type="datetime-local" i][readonly]::-webkit-inner-spin-button,
input[type="month" i][readonly]::-webkit-inner-spin-button,
input[type="week" i][readonly]::-webkit-inner-spin-button,
input[readonly]::-webkit-calendar-picker-indicator {
    visibility: hidden;
}

@supports not blink-feature(HTMLInputElementDropWebkitClearButton) {
    input[type="date" i]:disabled::-webkit-clear-button,
    input[type="datetime-local" i]:disabled::-webkit-clear-button,
    input[type="month" i]:disabled::-webkit-clear-button,
    input[type="week" i]:disabled::-webkit-clear-button,
    input[type="date" i][readonly]::-webkit-clear-button,
    input[type="datetime-local" i][readonly]::-webkit-clear-button,
    input[type="month" i][readonly]::-webkit-clear-button,
    input[type="week" i][readonly]::-webkit-clear-button {
        visibility: hidden;
    }
}

/* Form controls that measure the inline size without doing actual layout
   need to disable `text-autospace`, if their content can be affected by
   the property. crbug.com/1484863 */
input[type="date" i], input[type="datetime-local" i], input[type="month" i],
input[type="week" i], select {
    text-autospace: no-autospace !important;
}

select {
    appearance: auto;
    box-sizing: border-box;
    align-items: center;
    white-space: pre;
    -webkit-rtl-ordering: logical;
    color: FieldText;
    background-color: Field;
    border: 1px solid light-dark(#767676, #858585);
    cursor: default;
    border-radius: 0;
}

select:disabled {
    opacity: -internal-auto-base(0.7, unset);
}

/* -internal-list-box is how we specify select[multiple] */
/* select[multiple] is an exception to the prohibition on sizes here
   because it is one of the few controls with borders that grow on zoom
   (to solve a nasty scrollbar location problem) */
select:-internal-list-box {
    appearance: auto;
    border-radius: -internal-auto-base(2px, 0);
    align-items: -internal-auto-base(flex-start, initial);
    overflow-inline: -internal-auto-base(hidden, auto);
    overflow-block: -internal-auto-base(scroll, auto);
    vertical-align: -internal-auto-base(text-bottom, initial);
    white-space: -internal-auto-base(nowrap, inherit);
    field-sizing: -internal-auto-base(initial, content);
    border: -internal-auto-base(1px solid light-dark(#767676, #858585), 1px solid currentColor);
    box-sizing: -internal-auto-base(border-box, initial);
    block-size: -internal-auto-base(initial, calc(max(24px, 1lh) * attr(size type(<integer>), 4)));
}

select:not(:-internal-list-box) {
    overflow: visible !important;
}

/* The padding here should match the value of
   |extraPaddingForOptionInsideOptgroup| in list_picker.js, which is the
   padding for select optgroup option. */
select:-internal-list-box optgroup option {
    padding-inline-start: -internal-auto-base(20px, 0.5em);
}

select:-internal-list-box option,
select:-internal-list-box optgroup {
    line-height: -internal-auto-base(initial, revert-rule) !important;
}

/* option selected, list-box focused.
 * Sites are relying on the !important here: http://crbug.com/415953695 */
select:-internal-list-box:focus option:checked,
select:-internal-list-box:focus option:checked:hover {
    background-color: -internal-auto-base(SelectedItem, revert-rule) !important;
    color: -internal-auto-base(SelectedItemText, revert-rule) !important;
}
select:-internal-list-box:focus option:checked:disabled {
    background-color: -internal-auto-base(-internal-inactive-list-box-selection, revert-rule) !important;
}

/* option selected, list-box not focused */
select:-internal-list-box option:checked,
select:-internal-list-box option:checked:hover {
    background-color: -internal-auto-base(light-dark(#cecece, #545454), transparent);
    color: -internal-auto-base(light-dark(#101010, #FFFFFF), inherit);
}
select:-internal-list-box:not(:focus) option:checked:enabled:hover,
select:-internal-list-box:not(:focus) option:checked:enabled:active {
    background-color: -internal-auto-base(
        light-dark(#cecece, #545454),
        color-mix(currentColor 10%, transparent));
}
select:-internal-list-box option:checked:disabled:hover,
select:-internal-list-box option:checked:disabled:active {
    background-color: -internal-auto-base(
        light-dark(#cecece, #545454),
        color-mix(currentColor 50%, transparent));
}

select:-internal-list-box:disabled option:checked,
select:-internal-list-box option:checked:disabled,
select:-internal-list-box option:checked:disabled:hover {
    color: -internal-auto-base(light-dark(gray, #aaa), color-mix(currentColor 50%, transparent));
}
select:-internal-list-box:disabled option:checked {
    /* base color is set to inherit here because we are inheriting a color that
     * is already 50% transparent from select:disabled. */
   color: -internal-auto-base(light-dark(gray, #aaa), inherit);
}

/* TODO(crbug.com/406464760): decide on <hr> styles for customizable select
 * multiple. */
select:-internal-list-box hr {
    border-style: none;
    margin-block-start: 0.5em;
    margin-block-end: 0;
}

/* TODO(crbug.com/357649033): Consider undoing these styles for customizable
 * select. It is unlikely that they will be hit because customizable select
 * in-page is not focusable by default. */
select:-internal-list-box:focus-visible option:-internal-multi-select-focus {
    outline: auto 1px -webkit-focus-ring-color;
    outline-offset: -1px;
}

select option:enabled:hover {
    background-color: -internal-auto-base(initial, color-mix(currentColor 10%, transparent));
}

optgroup {
    font-weight: bolder;
    display: block;
}

optgroup::-internal-optgroup-label {
    padding: 0 2px 1px 2px;
    min-height: 1.2em;
}

option {
    font-weight: -internal-auto-base(normal, inherit);
    display: -internal-auto-base(block, flex);
    padding-inline: -internal-auto-base(2px, 0.5em);
    padding-block-start: 0;
    padding-block-end: -internal-auto-base(1px, 0);
    white-space: nowrap;
    min-inline-size: -internal-auto-base(unset, 24px);
    min-block-size: -internal-auto-base(1.2em, max(24px, 1lh));
    gap: -internal-auto-base(unset, 0.5em);
    align-items: -internal-auto-base(unset, center);
}

/* The following select style rules have to go after the other
   select styles in order to have higher precedence. */

/* TODO(crbug.com/880258): Use different styles for
  `-internal-autofill-previewed` and `-internal-autofill-selected`. */
input:-internal-autofill-previewed,
input:-internal-autofill-selected,
textarea:-internal-autofill-previewed,
textarea:-internal-autofill-selected,
select:-internal-autofill-previewed,
select:-internal-autofill-selected {
  appearance: menulist-button;
  background-image:none !important;
  background-color: light-dark(#E8F0FE, rgba(70,90,126,0.4)) !important;
  color: FieldText !important;
}

input:disabled,
textarea:disabled {
  @supports not blink-feature(AppearanceBase) {
     border-color: rgba(118, 118, 118, 0.3);
  }
  @supports blink-feature(AppearanceBase) {
    border-color: -internal-auto-base(rgba(118, 118, 118, 0.3), currentColor);
  }
}
select:disabled {
  border-color: -internal-auto-base(rgba(118, 118, 118, 0.3), currentColor);
}

select:disabled,
optgroup:disabled,
option:disabled,
select[disabled]>option {
    color: -internal-auto-base(
        light-dark(GrayText, #aaa),
        color-mix(currentColor 50%, transparent));
}
/* base color is set to inherit here because we are inheriting a color that
 * is already 50% transparent from select:disabled. */
select:disabled option,
optgroup:disabled option {
    color: -internal-auto-base(
        light-dark(GrayText, #aaa),
        inherit);
}

output {
    display: inline;
}

/* meter */

meter {
-webkit-user-modify: read-only !important;
appearance: auto;
block-size: 1em;
box-sizing: border-box;
display: inline-block;
inline-size: 5em;
vertical-align: -0.2em;
}

meter::-webkit-meter-inner-element {
-webkit-user-modify: read-only !important;
appearance: inherit;
block-size: 100%;
box-sizing: inherit;
display: grid;
grid-template-rows: 1fr [line1] 2fr [line2] 1fr;
inline-size: 100%;
position: relative;
}

meter::-webkit-meter-bar {
-webkit-user-modify: read-only !important;
align-self: unsafe center;
background: linear-gradient(to bottom, #ddd, #eee 20%, #ccc 45%, #ccc 55%, #ddd);
block-size: 100%;
box-sizing: border-box;
grid-row-end: line2;
grid-row-start: line1;
inline-size: 100%;
overflow: hidden;
position: absolute;
}

meter::-webkit-meter-bar:-internal-shadow-host-has-non-auto-appearance {
background: light-dark(#efefef, #3B3B3B);
border-radius: 20px;
border: thin solid light-dark(rgba(118, 118, 118, 0.3), #858585);
}

meter::-webkit-meter-optimum-value {
-webkit-user-modify: read-only !important;
background: linear-gradient(to bottom, #ad7, #cea 20%, #7a3 45%, #7a3 55%, #ad7);
block-size: 100%;
box-sizing: border-box;
}

meter::-webkit-meter-optimum-value:-internal-shadow-host-has-non-auto-appearance {
background: light-dark(#107c10, #74b374);
}

meter::-webkit-meter-suboptimum-value {
-webkit-user-modify: read-only !important;
background: linear-gradient(to bottom, #fe7, #ffc 20%, #db3 45%, #db3 55%, #fe7);
block-size: 100%;
box-sizing: border-box;
}

meter::-webkit-meter-suboptimum-value:-internal-shadow-host-has-non-auto-appearance {
background: light-dark(#ffb900, #f2c812);
}

meter::-webkit-meter-even-less-good-value {
-webkit-user-modify: read-only !important;
background: linear-gradient(to bottom, #f77, #fcc 20%, #d44 45%, #d44 55%, #f77);
block-size: 100%;
box-sizing: border-box;
}

meter::-webkit-meter-even-less-good-value:-internal-shadow-host-has-non-auto-appearance {
background: light-dark(#d83b01, #e98f6d);
}

/* progress */

progress {
    appearance: auto;
    box-sizing: border-box;

    @supports not blink-feature(AppearanceBase) {
        display: inline-block;
        block-size: 1em;
        inline-size: 10em;
        vertical-align: -0.2em;
    }

    @supports blink-feature(AppearanceBase) {
        display: -internal-auto-base(inline-block, unset);
        block-size: -internal-auto-base(1em, unset);
        inline-size: -internal-auto-base(10em, 100%);
        vertical-align: -internal-auto-base(-0.2em, unset);

        color: -internal-auto-base(unset, inherit);
        font: -internal-auto-base(unset, inherit);
        background-color: -internal-auto-base(unset, transparent);
    }
}

progress::-webkit-progress-inner-element {
    box-sizing: inherit;
    -webkit-user-modify: read-only;
    block-size: 100%;
    inline-size: 100%;

    @supports blink-feature(AppearanceBase) {
        /** This pseudo element doesn't exist in the standard layout. */
        display: -internal-auto-base(revert-rule, contents) !important;
    }
}

progress::-webkit-progress-bar {
    -webkit-user-modify: read-only !important;

    @supports not blink-feature(AppearanceBase) {
        background-color: gray;
        block-size: 100%;
        inline-size: 100%;
        box-sizing: border-box;
    }

    @supports blink-feature(AppearanceBase) {
        /* TODO(crbug.com/450139531): These styles are for progress::slider-track,
         * for now use the webkit pseudo elements. */
        background-color: -internal-auto-base(gray, transparent);
        block-size: -internal-auto-base(100%, 1em);
        inline-size: -internal-auto-base(100%, unset);
        box-sizing: -internal-auto-base(border-box, unset);

        border: -internal-auto-base(unset, 1px solid currentColor);
    }
}

progress::-webkit-progress-value {
    block-size: 100%;
    inline-size: 50%; /* should be removed later */
    -webkit-user-modify: read-only !important;

    @supports not blink-feature(AppearanceBase) {
        background-color: green;
        box-sizing: border-box;
    }

    @supports blink-feature(AppearanceBase) {
        /* TODO(crbug.com/450139531): These styles are for progress::slider-fill,
         * for now use the webkit pseudo elements. */
        background-color: -internal-auto-base(green, currentColor);
        box-sizing: -internal-auto-base(border-box, unset);
    }
}

/* inline elements */

u, ins {
    text-decoration: underline
}

abbr[title], acronym[title] {
    text-decoration: dotted underline;
}

strong, b {
    font-weight: bolder;
}

i, cite, em, var, address, dfn {
    font-style: italic
}

tt, code, kbd, samp {
    font-family: monospace
}

pre, xmp, plaintext, listing {
    display: block;
    font-family: monospace;
    white-space: pre;
    margin-block: 1__qem;
    margin-inline: 0;
}

mark {
    background-color: Mark;
    color: MarkText;
}

big {
    font-size: larger
}

small {
    font-size: smaller
}

s, strike, del {
    text-decoration: line-through
}

sub {
    vertical-align: sub;
    font-size: smaller
}

sup {
    vertical-align: super;
    font-size: smaller
}

nobr {
    white-space: nowrap
}

/* states */

:focus-visible {
    outline: auto 1px -webkit-focus-ring-color
}

button[interestfor] {
  user-select: none;
}

[interestfor]::interest-button {
  content: "?";
  display: inline-block;
  box-sizing: border-box;
  border: 1px solid currentColor;
  border-radius: 0.5em;
  color: inherit;
  background-color: transparent;
  padding-block: 0.25em;
  padding-inline: 0.5em;
  min-block-size: max(24px, 1lh);
  min-inline-size: 24px;
  text-align: center;
  margin-inline-start: 0.5em;
  user-select: none;
  cursor: help;
}

[interestfor]::interest-button:hover {
  background-color: color-mix(in lab, currentColor 10%, transparent);
}
[interestfor]::interest-button:active {
  background-color: color-mix(in lab, currentColor 20%, transparent);
}

html:focus-visible, body:focus-visible {
    outline: none
}

embed:focus-visible, iframe:focus-visible, object:focus-visible {
    outline: none
}

input:focus-visible, textarea:focus-visible, select:focus-visible {
    outline-offset: 0;
}

input[type="button" i]:focus-visible,
input[type="file" i]:focus-visible,
input[type="hidden" i]:focus-visible,
input[type="image" i]:focus-visible,
input[type="reset" i]:focus-visible,
input[type="submit" i]:focus-visible,
input[type="file" i]:focus-visible::-webkit-file-upload-button {
    outline-offset: 0
}

input[type="checkbox" i]:focus-visible,
input[type="radio" i]:focus-visible {
  outline-offset: 2px;
}


input[type="date" i]::-webkit-calendar-picker-indicator,
input[type="datetime-local" i]::-webkit-calendar-picker-indicator,
input[type="month" i]::-webkit-calendar-picker-indicator,
input[type="week" i]::-webkit-calendar-picker-indicator {
  background-image: light-dark(url(images/calendar_icon.svg), url(images/calendar_icon_white.svg));
  background-origin: content-box;
  background-repeat: no-repeat;
  background-size: contain;
  block-size: 1.0em;
  inline-size: 1.0em;
  opacity: 1;
  outline: none;
  padding: 2px;
}

input[type="time" i]::-webkit-calendar-picker-indicator {
  background-image: light-dark(url(images/time_icon.svg), url(images/time_icon_white.svg));
  background-origin: content-box;
  background-repeat: no-repeat;
  background-size: contain;
  opacity: 1;
  outline: none;
  margin-inline-start: 8px;
  padding-inline-start: 3px;
  padding-inline-end: 3px;
  padding-block: 3px;
  block-size: 1.05em;
  inline-size: 1.05em;
}

input[type="date" i]::-webkit-calendar-picker-indicator:focus-visible,
input[type="datetime-local" i]::-webkit-calendar-picker-indicator:focus-visible,
input[type="month" i]::-webkit-calendar-picker-indicator:focus-visible,
input[type="week" i]::-webkit-calendar-picker-indicator:focus-visible,
input[type="time" i]::-webkit-calendar-picker-indicator:focus-visible {
  outline-style: solid;
  outline-width: 2px;
  /* -webkit-focus-ring-color would ideally change from black to white when
  * color-scheme:dark is present, but it doesn't when we also set
  * outline-style:solid. */
  outline-color: light-dark(-webkit-focus-ring-color, white);
  outline-offset: -2px;
}

input::-webkit-calendar-picker-indicator:hover {
  background-color: initial;
}

input::-webkit-datetime-edit-ampm-field:focus,
input::-webkit-datetime-edit-day-field:focus,
input::-webkit-datetime-edit-hour-field:focus,
input::-webkit-datetime-edit-millisecond-field:focus,
input::-webkit-datetime-edit-minute-field:focus,
input::-webkit-datetime-edit-month-field:focus,
input::-webkit-datetime-edit-second-field:focus,
input::-webkit-datetime-edit-week-field:focus,
input::-webkit-datetime-edit-year-field:focus {
    background-color: light-dark(highlight, #99C8FF);
    color: light-dark(highlighttext, #000000);
    outline: none;
}

input::-webkit-datetime-edit-year-field[disabled],
input::-webkit-datetime-edit-month-field[disabled],
input::-webkit-datetime-edit-week-field[disabled],
input::-webkit-datetime-edit-day-field[disabled],
input::-webkit-datetime-edit-ampm-field[disabled],
input::-webkit-datetime-edit-hour-field[disabled],
input::-webkit-datetime-edit-millisecond-field[disabled],
input::-webkit-datetime-edit-minute-field[disabled],
input::-webkit-datetime-edit-second-field[disabled] {
    color: light-dark(GrayText, rgb(165, 165, 165));
}

a:-webkit-any-link {
    color: -webkit-link;
    text-decoration: underline;
    cursor: pointer;
}

a:-webkit-any-link:active {
    color: -webkit-activelink
}

a:-webkit-any-link:read-write {
    cursor: text;
}

a:-webkit-any-link:focus-visible {
  outline-offset: 1px;
}

/* HTML5 ruby elements */

ruby, rt {
    text-indent: 0; /* blocks used for ruby rendering should not trigger this */
}

ruby {
    display: ruby;
}

rt {
    line-height: normal;
    text-emphasis: none;
}

ruby > rt {
    display: ruby-text;
    font-size: 50%;
    text-align: start;
}

/* other elements */

frameset, frame {
    display: block
}

frameset {
    border-color: inherit
}

iframe {
    border: 2px inset
}

fencedframe {
    border: 2px inset;
    object-fit: contain !important;
    object-position: 50% 50% !important;
}

details {
    display: block
}

summary {
    display: block
}

/*
 * https://html.spec.whatwg.org/C/#the-details-and-summary-elements
 * The specification doesn't have |details >| and |:first-of-type|.
 * We add them because:
 *   - We had provided |summary { display: block }| for a long time,
 *     there are sites using <summary> without details, and they
 *     expect that <summary> is not a list-item.
 *   - Firefox does so.
 */
details > summary:first-of-type {
    display: list-item;
    counter-increment: list-item 0;
    list-style: disclosure-closed inside;
}

details[open] > summary:first-of-type {
    list-style-type: disclosure-open;
}

/* https://html.spec.whatwg.org/multipage/rendering.html#bidi-rendering */
/* This chunk of styles interacts with the `name == html_names::kDirAttr` case
   in HTMLElement::CollectStyleForPresentationAttribute(). Make sure any changes
   here are congruent with changes made there. */
address, blockquote, center, div, figure, figcaption, footer, form, header, hr,
legend, listing, main, p, plaintext, pre, summary, xmp, article, aside, h1, h2,
h3, h4, h5, h6, hgroup, nav, section, search, table, caption, colgroup, col,
thead, tbody, tfoot, tr, td, th, dir, dd, dl, dt, menu, ol, ul, li, bdi,
output, [dir=ltr i], [dir=rtl i], [dir=auto i] {
    unicode-bidi: isolate;
}
bdo, bdo[dir] {
    unicode-bidi: isolate-override;
}
textarea[dir=auto i], pre[dir=auto i] {
    unicode-bidi: plaintext;
}

dialog {
    /* https://html.spec.whatwg.org/multipage/rendering.html#flow-content-3 */
    position: absolute;
    inset-inline-start: 0;
    inset-inline-end: 0;
    width: fit-content;
    height: fit-content;
    margin: auto;
    border: solid;
    padding: 1em;
    background-color: Canvas;
    color: CanvasText;
}

/* Note that these can't use `dialog:modal` because a dialog stops matching
   :modal as soon as dialog.close() is called, but it needs to retain its
   styling until it's removed from the top layer, which can happen later due
   to animations of the `overlay` property. */
dialog:-internal-dialog-in-top-layer {
    /* https://html.spec.whatwg.org/multipage/rendering.html#flow-content-3 */
    position: fixed;
    overflow: auto;
    inset-block-start: 0;
    inset-block-end: 0;
    max-width: calc(100% - 6px - 2em);
    max-height: calc(100% - 6px - 2em);
    /* https://github.com/w3c/csswg-drafts/issues/6939#issuecomment-1016679588 */
    user-select: text;
    visibility: visible;
}

[popover] {
    position: fixed;
    position-anchor: auto;
    inset: 0;
    width: fit-content;
    height: fit-content;
    margin: auto;
    border: solid;
    padding: 0.25em;
    overflow: auto;
    color: CanvasText;
    background-color: Canvas;
}

/* dialog and popover handling of `display`. We need to be careful to get the
   `<dialog popover>` case working correctly, when open as a dialog.
   The `:where()` is added to lower the specificity so it doesn't take
   precedence over the [popover]:popover-open` rule just below. */
/* TODO(crbug.com/428039233): it would be cleaner if this was dialog:open,
   rather than dialog[open]. But that crashes. */
dialog:not([open]), [popover]:where(:not(:popover-open)) {
    display: none;
}
/* TODO(crbug.com/428039233): it would be cleaner if this was dialog:open,
   rather than dialog[open]. But that crashes. */
dialog[open], [popover]:popover-open {
    display: block;
}

dialog:-internal-dialog-in-top-layer::backdrop,
[popover]:-internal-popover-in-top-layer::backdrop {
    /* From the (modified) fullscreen spec: https://fullscreen.spec.whatwg.org/#user-agent-level-style-sheet-defaults: */
    position: fixed;
    inset: 0;
}

/* Note that these can't use `:modal` or `:popover-open`, because those pseudo
   classes stop matching as soon as the element is requested to be removed from
   the top layer (e.g. via popover.hidePopover() or dialog.close()). But the
   ::backdrop needs to be retained until the element is actually removed from
   the top layer, which can happen later due to animations of the
   `overlay` property. */
dialog:-internal-dialog-in-top-layer::backdrop {
    /* https://html.spec.whatwg.org/multipage/rendering.html#flow-content-3 */
    background-color: rgba(0,0,0,0.1);
}

[popover]:-internal-popover-in-top-layer::backdrop {
    pointer-events: none !important;
    background-color: transparent;
}

@supports blink-feature(OverlayProperty) {
  @supports blink-feature(OverlayGlobalRuleRemoval) {
    /* This is needed as a replacement for the *{overlay:none!important} rule
     * which is removed by the OverlayGlobalRuleRemoval flag. */
    dialog, [popover] {
      overlay: none !important;
    }
  }
  /* The `overlay:auto` UA rule goes away as soon as the modal is requested to
     close, or popover.hidePopover() is called. However, it can stay in the top
     layer after this point, if developer CSS animates the `overlay` property. */
  dialog:modal, [popover]:popover-open {
      overlay: auto !important;
  }
}

@supports blink-feature(MenuElements) {
    /* TODO(crbug.com/422803239): This should be combined with the [popover]
     * rule above when we remove this flag. */
    menulist:not(:popover-open) {
      display: none;
    }
}

slot {
    display: contents;
}

/* Pagination */

@page {
  /* https://drafts.csswg.org/css-page-3/#margin-text-alignment */
  @top-left-corner {
    text-align: right;
    vertical-align: middle;
  }
  @top-left {
    text-align: left;
    vertical-align: middle;
  }
  @top-center {
    text-align: center;
    vertical-align: middle;
  }
  @top-right {
    text-align: right;
    vertical-align: middle;
  }
  @top-right-corner {
    text-align: left;
    vertical-align: middle;
  }
  @right-top {
    text-align: center;
    vertical-align: top;
  }
  @right-middle {
    text-align: center;
    vertical-align: middle;
  }
  @right-bottom {
    text-align: center;
    vertical-align: bottom;
  }
  @bottom-right-corner {
    text-align: left;
    vertical-align: middle;
  }
  @bottom-right {
    text-align: right;
    vertical-align: middle;
  }
  @bottom-center {
    text-align: center;
    vertical-align: middle;
  }
  @bottom-left {
    text-align: left;
    vertical-align: middle;
  }
  @bottom-left-corner {
    text-align: right;
    vertical-align: middle;
  }
  @left-bottom {
    text-align: center;
    vertical-align: bottom;
  }
  @left-middle {
    text-align: center;
    vertical-align: middle;
  }
  @left-top {
    text-align: center;
    vertical-align: top;
  }
}

/* Allows table headers and footers to print at the top / bottom of each
   page. Querying overflow-block since media() does not support media types. */
thead { break-inside: if(media(overflow-block: paged): avoid;) }
tfoot { break-inside: if(media(overflow-block: paged): avoid;) }

/* spelling/grammar error pseudos */

html::spelling-error {
    text-decoration: -internal-spelling-error-color spelling-error;
}

html::grammar-error {
    text-decoration: -internal-grammar-error-color grammar-error;
}

img:is([sizes="auto" i], [sizes^="auto," i]) {
  contain: size !important;
  contain-intrinsic-size: 300px 150px;
}

/* https://drafts.csswg.org/css-ui-4/#inertness */
/* Reducing specificity with :where since [inert] needs to override. Also
   explicitly use 'dialog' to avoid adding universal bucket rule. Separate rule
   added for :fullscreen in fullscreen.css. */
dialog:where(:modal) {
  interactivity: auto;
}

[inert] {
  interactivity: inert !important;
}

/* noscript is handled internally, as it depends on settings. */

/* These styles are identical to the not blink-feature block above, except
 * that the :not([multiple]) part is removed. */
select:not(:-internal-list-box) {
  font: -internal-auto-base(-webkit-small-control, inherit);
  text-shadow: -internal-auto-base(none, inherit);
  text-transform: -internal-auto-base(none, initial);
  text-rendering: -internal-auto-base(auto, inherit);
  letter-spacing: -internal-auto-base(normal, inherit);
  word-spacing: -internal-auto-base(normal, inherit);
  text-align: -internal-auto-base(start, initial);
  text-indent: -internal-auto-base(0px, initial);
  -webkit-rtl-ordering: -internal-auto-base(logical, inherit);
  cursor: -internal-auto-base(default, inherit);
  white-space: -internal-auto-base(pre, inherit);
  /* This text-autospace rule won't work because it is set with !important
   * earlier in the UA stylesheet. After merging with the rest of the UA
   * style rules when removing the CustomizableSelect flag, it should start
   * to work. */
  text-autospace: -internal-auto-base(no-autospace !important, inherit);
  color: -internal-auto-base(FieldText, inherit);
  background-color: -internal-auto-base(Field, transparent);
  border: 1px solid -internal-auto-base(light-dark(#767676, #858585), currentColor);
  padding-block: -internal-auto-base(0, 0.25em);
  padding-inline: -internal-auto-base(0, 0.5em);

  /* min-size rules ensure that we meet accessibility guidelines for minimum target size.
   * https://github.com/openui/open-ui/issues/1026
   * https://www.w3.org/WAI/WCAG22/Understanding/target-size-minimum.html */
  /* TODO(crbug.com/41483940): This might be able to be combined with the
   * default select option rules at some point. This should be re-evaluated
   * before StylableSelect is shipped. */
  min-inline-size: -internal-auto-base(auto, calc-size(auto, max(size, 24px)));
  /* The 1lh here makes sure that options with no text still make the button
   * have the same height as options with text. */
  min-block-size: -internal-auto-base(auto, calc-size(auto, max(size, 24px, 1lh)));

  gap: -internal-auto-base(initial, 0.5em);
  border-radius: -internal-auto-base(0, 0.5em);
  align-items: -internal-auto-base(center, unset);
  /* https://github.com/whatwg/html/issues/10876 */
  user-select: -internal-auto-base(auto, none);
}
select {
  font: -internal-auto-base(-webkit-small-control, inherit);
  text-shadow: -internal-auto-base(none, inherit);
  text-transform: -internal-auto-base(none, initial);
  text-rendering: -internal-auto-base(auto, inherit);
  letter-spacing: -internal-auto-base(normal, inherit);
  word-spacing: -internal-auto-base(normal, inherit);
  text-align: -internal-auto-base(start, initial);
  text-indent: -internal-auto-base(0px, initial);
  -webkit-rtl-ordering: -internal-auto-base(logical, inherit);
  cursor: -internal-auto-base(default, inherit);
  white-space: -internal-auto-base(pre, inherit);
  /* See note in CustomizableSelect feature block about text-autospace. */
  text-autospace: -internal-auto-base(no-autospace !important, inherit);
  color: -internal-auto-base(FieldText, inherit);
  background-color: -internal-auto-base(Field, transparent);
  /* See notes about min-inline-size/min-block-size in CustomizableSelect feature block. */
  min-inline-size: -internal-auto-base(auto, calc-size(auto, max(size, 24px)));
  min-block-size: -internal-auto-base(auto, calc-size(auto, max(size, 24px, 1lh)));
  /* https://github.com/whatwg/html/issues/10876 */
  user-select: -internal-auto-base(auto, none);
}

@supports not blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box):not([multiple]):not([popover]) {
    display: -internal-auto-base(inline-block, inline-flex);
  }
}
@supports blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box):not([popover]) {
    display: -internal-auto-base(inline-block, inline-flex);
  }
}

@supports not blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box):not([multiple]) > button:first-child {
    all: unset;
    display: contents;
    interactivity: inert !important;
  }
}
@supports blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box) > button:first-child {
    all: unset;
    display: contents;
    interactivity: inert !important;
  }
}

@supports not blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box):not([multiple]):enabled:hover {
    background-color: -internal-auto-base(Field, color-mix(currentColor 10%, transparent));
  }
  select:not(:-internal-list-box):not([multiple]):enabled:active {
    background-color: -internal-auto-base(Field, color-mix(currentColor 20%, transparent));
  }
  select:not(:-internal-list-box):not([multiple]):disabled {
    opacity: -internal-auto-base(0.7, unset);
    color: -internal-auto-base(light-dark(GrayText, #aaa), color-mix(currentColor 50%, transparent));
    border-color: -internal-auto-base(rgba(118, 118, 118, 0.3), inherit);
  }
}
@supports blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box):enabled:hover {
    background-color: -internal-auto-base(Field, color-mix(currentColor 10%, transparent));
  }
  select:not(:-internal-list-box):enabled:active {
    background-color: -internal-auto-base(Field, color-mix(currentColor 20%, transparent));
  }
  select:not(:-internal-list-box):disabled {
    opacity: -internal-auto-base(0.7, unset);
    color: -internal-auto-base(light-dark(GrayText, #aaa), color-mix(currentColor 50%, transparent));
    border-color: -internal-auto-base(rgba(118, 118, 118, 0.3), inherit);
  }
}

/* Undo unwanted styles from select rules */
@supports not blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box):not([multiple]) > button:first-child,
  select::picker(select) {
    white-space: normal;
  }
}
@supports blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box) > button:first-child,
  select::picker(select) {
    white-space: normal;
  }
}

select:not(:-internal-list-box)::picker(select) {
  box-sizing: border-box;
  border: 1px solid -internal-auto-base(light-dark(#767676, #858585), currentColor);
  border-radius: -internal-auto-base(2px, 0);
  padding: 0;
  color: -internal-auto-base(inherit, CanvasText);
  background-color: Canvas;
  margin: 0;
  inset: auto;
  min-inline-size: anchor-size(self-inline);
  /* TODO(crbug.com/409942762): Consider removing -internal-auto-base() here
   * if underlying performance issues with lh units are fixed. */
  min-block-size: -internal-auto-base(0, 1lh);
  /* Go to the edge of the viewport, and add scrollbars if needed. */
  max-block-size: stretch;
  overflow: auto;
  /* Below and span-right, by default. */
  position-area: self-block-end span-self-inline-end;
  position-try-order: most-block-size;
  position-try-fallbacks:
    self-block-start span-self-inline-end,
    self-block-end span-self-inline-start,
    self-block-start span-self-inline-start;
}

select:not(:-internal-list-box) option {
  /* min-size rules ensure that we meet accessibility guidelines for minimum target size.
   * https://github.com/openui/open-ui/issues/1026
   * https://www.w3.org/WAI/WCAG22/Understanding/target-size-minimum.html */
  /* TODO(crbug.com/41483940): This might be able to be combined with the
   * default select option rules at some point. This should be re-evaluted
   * before CustomizableSelect is shipped. */
  min-inline-size: 24px;
  /* TODO(crbug.com/409942762): Consider removing -internal-auto-base() here
   * if underlying performance issues with lh units are fixed. */
  min-block-size: -internal-auto-base(24px, max(24px, 1lh));
  font-weight: -internal-auto-base(normal, inherit);
  align-items: center;
  gap: 0.5em;
}
select:not(:-internal-list-box):not([multiple]) option {
  padding-inline: -internal-auto-base(2px, 0.5em);
  padding-block-end: -internal-auto-base(1px, 0);
  display: -internal-auto-base(block, flex);
}
/* In the multiple case, we want to use the same styles as base appearance
 * because the picker is rendered as a popover. */
select:not(:-internal-list-box)[multiple] option {
  padding-inline: 0.5em;
  padding-block-end: 0;
  display: flex;
}

select:not(:-internal-list-box) option:enabled:hover {
  background-color: color-mix(currentColor 10%, transparent);
}
select:not(:-internal-list-box) option:enabled:active {
  background-color: color-mix(currentColor 20%, transparent);
}
select:not(:-internal-list-box) option:disabled {
  color: -internal-auto-base(inherit, color-mix(currentColor 50%, transparent));
}
select:not(:-internal-list-box)[multiple] option:disabled {
/* This rule applies appearance:base styles to the appearance:auto
 * <select multiple size=1>. Without it, disabled options would not appear disabled. */
  color: color-mix(currentColor 50%, transparent);
}
/* :-internal-list-box is needed here in order to get precedence over this
 * selector: select:-internal-list-box option:enabled:hover */
select:-internal-list-box option:enabled:active {
  background-color: color-mix(currentColor 20%, transparent);
}

select option::checkmark {
  content: '\2713' / '';
}

/* The svg data urls in the below ::checkmark rules are built to match the
 * checkbox rendering in NativeThemeBase. */
select[multiple] option::checkmark {
  /* The svg is 13px by 13px. Without this height rule, the svg would not be
   * vertically centered within the ::checkmark. */
  height: -internal-auto-base(13px, initial);
  content: -internal-auto-base(url(data:image/svg+xml,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20width%3D%2213%22%20height%3D%2213%22%20viewBox%3D%220%200%2013%2013%22%20fill%3D%22none%22%3E%3Crect%20x%3D%220.5%22%20y%3D%220.5%22%20width%3D%2212%22%20height%3D%2212%22%20rx%3D%222%22%20fill%3D%22%23ffffff%22%20stroke%3D%22%23767676%22%20stroke-width%3D%221%22%2F%3E%3C%2Fsvg%3E), '\2713' / '');
}
select[multiple] option:checked::checkmark {
  content: -internal-auto-base(url(data:image/svg+xml,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20width%3D%2213%22%20height%3D%2213%22%20viewBox%3D%220%200%2013%2013%22%20fill%3D%22none%22%3E%3Crect%20x%3D%220%22%20y%3D%220%22%20width%3D%2213%22%20height%3D%2213%22%20rx%3D%222%22%20fill%3D%22%230075FF%22%2F%3E%3Cpath%20d%3D%22M2.6%207%20l2.6%202.5%20L10.4%202.6%22%20stroke%3D%22%23ffffff%22%20stroke-width%3D%222%22%2F%3E%3C%2Fsvg%3E), '\2713' / '');
}
select[multiple] option:disabled::checkmark {
  content: -internal-auto-base(url(data:image/svg+xml,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20width%3D%2213%22%20height%3D%2213%22%20viewBox%3D%220%200%2013%2013%22%20fill%3D%22none%22%3E%3Crect%20x%3D%220.5%22%20y%3D%220.5%22%20width%3D%2212%22%20height%3D%2212%22%20rx%3D%222%22%20fill%3D%22%23ffffff%22%20stroke%3D%22%23767676%22%20stroke-opacity%3D%2260%25%22%20fill-opacity%3D%2260%25%22%20stroke-width%3D%221%22%2F%3E%3C%2Fsvg%3E), '\2713' / '');
}
select[multiple] option:checked:disabled::checkmark {
  content: -internal-auto-base(url(data:image/svg+xml,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20width%3D%2213%22%20height%3D%2213%22%20viewBox%3D%220%200%2013%2013%22%20fill%3D%22none%22%3E%3Crect%20x%3D%220%22%20y%3D%220%22%20width%3D%2213%22%20height%3D%2213%22%20rx%3D%222%22%20fill%3D%22%23767676%22%20fill-opacity%3D%2260%25%22%2F%3E%3Cpath%20d%3D%22M2.6%207%20l2.6%202.5%20L10.4%202.6%22%20stroke%3D%22%23ffffff%22%20stroke-opacity%3D%2260%25%22%20stroke-width%3D%222%22%2F%3E%3C%2Fsvg%3E), '\2713' / '');
}

select option:not(:checked)::checkmark {
  /* appearance:auto renders an unchecked box instead of empty space. */
  visibility: -internal-auto-base(visible, hidden);
}

select:-internal-autofill-selected,
select::-internal-select-autofill-preview[popover] {
  background-image: none;
  background-color: light-dark(#E8F0FE, rgba(70, 90, 126, 0.4));
  color: FieldText;
}
select::-internal-select-autofill-preview[popover]:popover-open {
  display: grid;
  align-items: center;
  position-area: center;
  height: calc(anchor-size(height) - 2px);
  width: calc(anchor-size(width) - 2px);
  margin: 0;
  padding: 0;
  border: 1px solid black;
}
select::-internal-select-autofill-preview-text {
  overflow: hidden;
  text-overflow: ellipsis;
  text-align: center;
  white-space: nowrap;
  font: -webkit-small-control !important;
  font-feature-settings: normal !important;
}

@supports not blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box):not([multiple])::picker-icon {
    content: -internal-auto-base(none, counter(fake-counter-name, disclosure-open));
    /* We don't have to use -internal-auto-base() here because
     * the pseudo-element won't get generated unless the content property is set. */
    display: block;
    margin-inline-start: auto;
  }
}
@supports blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box)::picker-icon {
    content: -internal-auto-base(none, counter(fake-counter-name, disclosure-open));
    display: block;
    margin-inline-start: auto;
  }
}

select:-internal-list-box::picker-icon {
  display: none !important;
}

select optgroup::-internal-optgroup-label {
  padding-inline: -internal-auto-base(2px, 0.5em);
  padding-block: -internal-auto-base(0 1px, 0);
  min-height: -internal-auto-base(1.2em, auto);
}
select optgroup legend {
  padding-inline: -internal-auto-base(2px, 0.5em);
  min-block-size: -internal-auto-base(initial, 1lh);
}
/* This selector is unnecessarily long in order to have higher precedence
 * than the earlier `select:not(:-internal-list-box) option` selector. */
select:-internal-list-box optgroup option,
select:not(:-internal-list-box) optgroup option {
  padding-inline-start: -internal-auto-base(20px, 0.5em);
  font-weight: normal;
}

/* This rule applies appearance:base styles to the appearance:auto
 * <select multiple size=1> optgroups. Without it, the padding would look too
 * small. */
select:not(:-internal-list-box)[multiple] optgroup::-internal-optgroup-label,
select:not(:-internal-list-box)[multiple] optgroup legend {
  padding-inline: 0.5em;
  padding-block: 0;
}
select:not(:-internal-list-box)[multiple] optgroup option {
  padding-inline-start: -internal-auto-base(1em, 0.5em);
  font-weight: normal;
}

/* These style rules control whether the select's MenuListInnerElement or
 * author provided <button> are rendered. Only one should be rendered at a
 * time, and is based on whether the author provided a <button> and whether
 * appearance:base-select is set. */
select:not(:-internal-select-has-slotted-button)::-internal-select-button-slot {
  display: none;
}
select:-internal-select-has-slotted-button::-internal-select-inner-element {
  display: -internal-auto-base(block, none);
}
select:-internal-select-has-slotted-button::-internal-select-button-slot {
  display: -internal-auto-base(none, contents);
}

/* These style rules switch whether <option> elements render their label text
 * via ::-internal-option-label-container or all of their children via a
 * <slot> called ::-internal-option-slot. Using the <slot> for rendering is
 * only supported for customizable select when the option does not have a
 * label attribute. In all other cases, just the label text is rendered via
 * ::-internal-option-label-container. */
/* TODO(crbug.com/393500003): Some :-internal-list-box and multiple checks
 * here could be removed if we make -internal-auto-base() work better. */
option::-internal-option-label-container {
  display: -internal-auto-base(contents, none);
}
option::-internal-option-slot {
  display: -internal-auto-base(none, contents);
}
/* Render the label attribute when it is set. This should be kept in sync
 * with the logic in HTMLOptionElement::DisplayLabel. */
option[label]:not([label=""])::-internal-option-label-container {
  display: contents;
}
option[label]:not([label=""])::-internal-option-slot {
  display: none;
}

/* Don't allow nested <optgroup>s. */
select optgroup optgroup {
  display: none;
}

@supports blink-feature(MenuElements) {
  menubar {
    display: inline-flex;
    flex-direction: row;
    gap: 0.5em;
    width: max-content;
    background-color: transparent;
    border: 1px solid currentColor;
    border-radius: 0.25em;
    padding: 0.25em;
  }

  menulist {
    display: block;
    position: fixed;
    position-anchor: auto;
    margin: 0;
    inset: auto;
    /* TODO(https://crbug.com/406566432): width:max-content probably isn't
     * ideal, but ::picker(select) has the same desired behavior without
     * setting width. We should figure out how ::picker(select) does this and
     * copy it here. */
    width: max-content;
    max-block-size: stretch;
    overflow: auto;
    color: CanvasText;
    background-color: Canvas;
    border: 1px solid currentColor;
    padding: 0.25em;
  }

  menulist:-internal-menulist-popover-with-menubar-anchor {
    /* Below and span-right, by default. */
    position-area: block-end span-inline-end;
  }

  menulist:-internal-menulist-popover-with-menulist-anchor {
    /* To the right, with its top aligned to the implicit anchor's top */
    position-area: inline-end span-block-end;
  }

  menulist > fieldset {
    /* TODO(https://crbug.com/406566432): Consider making this
     * `display: contents`. */
    margin-inline: 0;
    border: none;
    padding-block: 0;
    padding-inline: 0;
  }

  /* TODO(https://crbug.com/406566432): Should this be a descendant combinator
   * instead? */
  menulist > hr {
    color: inherit;
    margin-inline: 0;
    border: none;
    border-block-start: 1px solid currentColor;
  }

  menuitem::checkmark {
    content: '\2713' / '';
  }

  menuitem:not(:checked)::checkmark {
    visibility: hidden;
  }

  menuitem::expand-icon {
    content: counter(fake-counter-name, disclosure-closed);
    /* margin-inline-start adds a gap in between the text inside the menuitem
     * and the ::expand-icon. This matches select::picker-icon. */
    margin-inline-start: auto;
  }

  /* We can use the direct child selector for menuitems in menubars, because the
   * menubar content model does not allow for fieldset as an intermediate to
   * group menuitems in menubars. */
  menubar > menuitem {
    display: inline-flex;
  }
  menulist menuitem {
    display: flex;
  }

  menubar, menulist {
    menuitem {
      align-items: center;
      user-select: none;
      gap: 0.5em;

      /* The min-*-size rules below were inspired by the same rules for
       * customizable select, and mostly cater to WCAG accessibility guidelines
       * of making controls a minimum of 24x24px. See:
       * https://github.com/openui/open-ui/issues/1026
       * https://www.w3.org/WAI/WCAG22/Understanding/target-size-minimum.html */
      min-inline-size: 24px;
      min-block-size: max(24px, 1lh);

      font-weight: inherit;
      padding-inline: 0.5em;
    }

    menuitem:enabled:hover {
      background-color: color-mix(currentColor 10%, transparent);
    }
    menuitem:disabled {
      color: color-mix(currentColor 50%, transparent);
    }
  }
}

[overscrollcontainer] {
  -internal-overscroll-area: auto;
}
[overscrollcontainer="overlay"] {
  -internal-overscroll-area: overlay;
}
[overscrollarea],
:-internal-overscroll-target {
  -internal-overscroll-position: auto;
}

@supports blink-feature(CustomizableCombobox) {
  /* This would be set as an inline style in DataListIndicatorElement, but
   * -internal-auto-base() can only be used in the UA stylesheet.
   * :-internal-text-field is needed for this because many attribute selectors
   * would not be performant enough. */
  input:-internal-text-field::-webkit-calendar-picker-indicator {
    display: -internal-auto-base(list-item, none);
  }

  /* TODO(crbug.com/481324376): Consider making these styles not use
   * :popover-open to avoid potential compat issues. */
  datalist:popover-open {
    /* [popover] styles */
    position: fixed;
    inset: 0;
    position-anchor: auto;
    width: fit-content;
    height: fit-content;
    margin: auto;
    border: solid;
    padding: 0.25em;
    overflow: auto;
    color: CanvasText;
    background-color: Canvas;

    /* [popover]:popover-open styles */
    display: block;

    /* ::picker(select) styles */
    box-sizing: border-box;
    border: 1px solid;
    padding: 0;
    color: inherit;
    background-color: Canvas;
    margin: 0;
    inset: auto;
    min-inline-size: anchor-size(self-inline);
    /* Go to the edge of the viewport, and add scrollbars if needed. */
    max-block-size: stretch;
    overflow: auto;
    /* Below and span-right, by default. */
    position-area: self-block-end span-self-inline-end;
    position-try-order: most-block-size;
    position-try-fallbacks:
        self-block-start span-self-inline-end,   /* First try above and span-right. */
        self-block-end span-self-inline-start,   /* Then below but span-left. */
        self-block-start span-self-inline-start; /* Then above and span-left. */
  }

  datalist option {
    min-inline-size: 24px;
    /* TODO(crbug.com/409942762): Consider removing -internal-auto-base() here
     * if underlying performance issues with lh units are fixed. */
    min-block-size: -internal-auto-base(24px, max(24px, 1lh));
    font-weight: -internal-auto-base(normal, inherit);
    padding-inline: -internal-auto-base(2px, 0.5em);
    padding-block-end: -internal-auto-base(1px, 0);
  }

  /* These are redundant with the style rules in the FilterableSelect block.
   * They should be removed when the FilterableSelect flag is removed. */
  datalist option:active-option {
    outline: black auto 1px;
  }
  option:filtered {
    display: none;
  }
}

@supports blink-feature(FilterableSelect) {
  option:active-option {
    outline: black auto 1px;
  }
  option:filtered {
    display: none;
  }
}
)BlinkUA";

// IDR_UASTYLE_QUIRKS_CSS: third_party/blink/renderer/core/html/resources/quirks.css
constexpr char kResource1[] = R"BlinkUA(
/* 
 * Additonal style sheet used to render HTML pages in quirks mode.
 *
 * Copyright (C) 2000-2003 Lars Knoll (knoll@kde.org)
 * Copyright (C) 2004, 2006, 2007 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

/* This sheet is appended to html.css before parsing which means the selectors
   below are in the default html namespace:

   @namespace "http://www.w3.org/1999/xhtml"
*/

/* Give floated images margins of 3px */
img[align="left" i] {
    margin-right: 3px;
}
img[align="right" i] {
    margin-left: 3px;
}

/* Tables reset both line-height and white-space in quirks mode. */
/* Compatible with WinIE. Note that font-family is *not* reset. */
table {
    white-space: normal;
    line-height: normal;
    font-weight: normal;
    font-size: medium;
    font-variant: normal;
    font-style: normal;
    color: -internal-quirk-inherit;
    text-align: start;
}

/* This will apply only to text fields, since all other inputs already use border box sizing */
input:not([type=image i]), textarea {
    box-sizing: border-box;
}

/* Set margin-bottom for form element in quirks mode. */
/* Compatible with Gecko. (Doing this only for quirks mode is a fix for bug 17696.) */
form {
    margin-block-end: 1em
}

/* https://html.spec.whatwg.org/multipage/rendering.html#lists */
li { list-style-position: inside; }

/* Expand `:is()` in the rightmost position because otherwise they hit
  `DCHECK(default_html_quirks_style_->UniversalRules().empty())` */
/* li :is(dir, menu, ol, ul) { list-style-position: outside; } */
li dir, li menu, li ol, li ul { list-style-position: outside; }

/* :is(dir, menu, ol, ul) :is(dir, menu, ol, ul, li) { */
:is(dir, menu, ol, ul) dir,
:is(dir, menu, ol, ul) menu,
:is(dir, menu, ol, ul) ol,
:is(dir, menu, ol, ul) ul,
:is(dir, menu, ol, ul) li {
    list-style-position: unset;
}
)BlinkUA";

// IDR_UASTYLE_VIEW_SOURCE_CSS: third_party/blink/renderer/core/css/view-source.css
constexpr char kResource2[] = R"BlinkUA(
/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

body {
    margin: 0
}

table {
    width: max-content;
    min-width: 100vw;
    border-spacing: 0;
    white-space: pre;
    margin: 0;
    font-size: initial;
    font-family: monospace;
    tab-size: 4;
}

.line-wrap {
    width: 100%;
    white-space: pre-wrap;
    word-break: normal;
    overflow-wrap: anywhere;
}

.line-wrap-control {
    width: 100%;
    font-size: initial;
    font-family: monospace;
    user-select: none;
    background-color: light-dark(rgb(240, 240, 240), rgb(60, 60, 60));
    border-bottom: 1px solid rgb(187, 187, 187);
    display: flex;
    justify-content: flex-start;
    align-items: center;
}

.line-wrap-cell {
  white-space: normal;
}

td {
    padding: 0;
    vertical-align: baseline
}

.line-gutter-backdrop, .line-number {
    /* Keep this in sync with inspector.css (.webkit-line-gutter-backdrop) */
    box-sizing: border-box;
    padding: 0 4px;
    width: 31px;
    background-color: light-dark(rgb(240, 240, 240), rgb(60, 60, 60));
    border-right: 1px solid rgb(187, 187, 187);
    user-select: none;
}

.line-gutter-backdrop {
    /* Keep this in sync with inspector.css (.webkit-line-gutter-backdrop) */
    position: absolute;
    z-index: -1;
    left: 0;
    top: 0;
    height: 100%
}

.line-number {
    text-align: right;
    color: light-dark(rgb(148, 132, 132), rgb(128, 128, 128));
    word-break: normal;
    white-space: nowrap;
    font-size: 9px;
    font-family: Helvetica;
    user-select: none;
}

.line-number::before {
    content: attr(value);
}

tbody:last-child .line-content:empty:before {
    content: " ";
}

.line-content {
    padding: 0 5px;
}

.html-tag {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-tag) */
    color: light-dark(rgb(136, 18, 128), rgb(93, 176, 215));
}

.html-attribute-name {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-attribute-name) */
    color: light-dark(rgb(153, 69, 0), rgb(155 187 220));
}

.html-attribute-value {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-attribute-value) */
    color: light-dark(rgb(26, 26, 166), rgb(242, 151, 102));
}

.html-external-link, .html-resource-link {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-external-link, .webkit-html-resource-link) */
    color: light-dark(#00e, rgb(159, 180, 214));
}

.html-external-link {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-external-link) */
    text-decoration: none;
}

.html-external-link:hover {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-external-link:hover) */
    text-decoration: underline;
}

.html-comment {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-comment) */
    color: rgb(35, 110, 37);
}

.html-processing-instruction {
    color: light-dark(rgb(0, 96, 96), rgb(100, 200, 200));
}

.html-doctype {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-doctype) */
    color: rgb(192, 192, 192);
}

.html-end-of-file {
    /* Keep this in sync with inspectorSyntaxHighlight.css (.webkit-html-end-of-file) */
    color: rgb(255, 0, 0);
    font-weight: bold;
}
)BlinkUA";

// IDR_UASTYLE_THEME_CHROMIUM_ANDROID_CSS: third_party/blink/renderer/core/html/resources/android.css
constexpr char kResource3[] = R"BlinkUA(
/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* These styles override other user-agent styles for Chromium on Android. */

/* This sheet is appended to html.css before parsing which means the selectors
   below are in the default html namespace:

   @namespace "http://www.w3.org/1999/xhtml"
*/

input[type="date" i]:disabled,
input[type="datetime-local" i]:disabled,
input[type="month" i]:disabled,
input[type="time" i]:disabled,
input[type="week" i]:disabled,
input[type="date" i]:read-only,
input[type="datetime-local" i]:read-only,
input[type="month" i]:read-only,
input[type="time" i]:read-only,
input[type="week" i]:read-only {
    background-color: ButtonFace;
    color: GrayText;
}

input[type="date" i],
input[type="datetime-local" i],
input[type="month" i],
input[type="time" i],
input[type="week" i] {
    align-items: center;
    appearance: auto;
    background-color: ButtonFace;
    border: 1px solid #a9a9a9;
    display: -webkit-inline-flex;
    overflow: hidden;
    width: 10em;
}

input[type="datetime-local" i] {
    width: 15em;
}

input::-webkit-date-and-time-value {
    margin: 1px 24px 1px 4px;
    overflow: hidden;
    white-space: pre;
}
)BlinkUA";

// IDR_UASTYLE_FULLSCREEN_ANDROID_CSS: third_party/blink/renderer/core/css/fullscreenAndroid.css
constexpr char kResource4[] = R"BlinkUA(
video:fullscreen {
  /* Fullscreen video on Android does not synchronize correctly when the <video>
   * element is not rendered in the root render pass. Disable properties that
   * cause this. (http://crbug.com/618753) */
  opacity: 1 !important;
  filter: none !important;
  border-radius: 0 !important;
  mix-blend-mode: normal !important;
}
)BlinkUA";

// IDR_UASTYLE_THEME_CHROMIUM_LINUX_CSS: third_party/blink/renderer/core/html/resources/linux.css
constexpr char kResource5[] = R"BlinkUA(
/*
 * Copyright (C) 2009 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* These styles override other user-agent styles for Chromium on Linux. */

/* This sheet is appended to html.css before parsing which means the selectors
   below are in the default html namespace:

   @namespace "http://www.w3.org/1999/xhtml"
*/

select:not(:-internal-list-box) {
    /* Selects with popup menus look like buttons with a drop down triangle on Linux. */
    background-color: ButtonFace;
}

input[type=range i] {
    color: #9d968E;
}

select:not(:-internal-list-box):not([multiple]):not(:-internal-list-box):not([multiple]) {
  background-color: -internal-auto-base(ButtonFace, transparent);
}
select:not(:-internal-list-box):not([multiple]):enabled:hover {
  background-color: -internal-auto-base(ButtonFace, color-mix(currentColor 10%, transparent));
}
select:not(:-internal-list-box):not([multiple]):enabled:active {
  background-color: -internal-auto-base(ButtonFace, color-mix(currentColor 20%, transparent));
}

@supports blink-feature(CustomizableSelectMultiplePopup) {
  select:not(:-internal-list-box)[multiple]:not(:-internal-list-box)[multiple] {
    background-color: -internal-auto-base(ButtonFace, transparent);
  }
  select:not(:-internal-list-box)[multiple]:enabled:hover {
    background-color: -internal-auto-base(ButtonFace, color-mix(currentColor 10%, transparent));
  }
  select:not(:-internal-list-box)[multiple]:enabled:active {
    background-color: -internal-auto-base(ButtonFace, color-mix(currentColor 20%, transparent));
  }
}
)BlinkUA";

// IDR_UASTYLE_THEME_MAC_CSS: third_party/blink/renderer/core/html/resources/mac.css
constexpr char kResource6[] = R"BlinkUA(
/* Copyright 2014 The Chromium Authors
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* This sheet is appended to html.css before parsing which means the selectors
   below are in the default html namespace:

   @namespace "http://www.w3.org/1999/xhtml"
*/

select, input[type="color" i][list] {
    /* TODO(tkent): Use ButtonFace and border same as buttons. */
    background-color: #f8f8f8;
    border: 1px solid #a6a6a6;
}

select:-internal-list-box  {
    background-color: white;
    border: 1px solid #999999;
}

input::-webkit-inner-spin-button {
    align-self: center;
}

input[type="button" i],
input[type="submit" i],
input[type="reset" i],
input[type="file" i]::-webkit-file-upload-button,
button {
    /* The color is similar to the border of OSX 10.12 buttons. */
    border-color: #d8d8d8 #d1d1d1 #bababa;
    border-style: solid;
    border-width: 1px;
    /* Fixed padding provided by ThemeMac::ControlPadding() - 1px for broder */
    padding: 1px 7px 2px;
}

:focus-visible {
    outline: auto 5px -webkit-focus-ring-color
}
)BlinkUA";

// IDR_UASTYLE_SCROLL_BUTTON_CSS: third_party/blink/renderer/core/css/scroll_button.css
constexpr char kResource7[] = R"BlinkUA(
::scroll-button(*) {
  appearance: auto;
  -internal-align-content-block: center;
  margin: 0__qem;
  font: -webkit-small-control;
  text-rendering: auto; /* FIXME: Remove when tabs work with optimizeLegibility. */
  letter-spacing: normal;
  word-spacing: normal;
  line-height: normal;
  text-transform: none;
  text-indent: 0;
  text-shadow: none;
  display: inline-block;
  text-align: center;
  cursor: default;
  padding-block: 1px;
  padding-inline: 6px;
  border: 2px outset ButtonBorder;
  box-sizing: border-box;
  background-color: ButtonFace;
  color: ButtonText;
  align-items: flex-start;
}

::scroll-button(*):disabled {
  background-color: light-dark(rgba(239, 239, 239, 0.3), rgba(19, 1, 1, 0.3));
  border-color: light-dark(rgba(118, 118, 118, 0.3), rgba(195, 195, 195, 0.3));
  color: light-dark(rgba(16, 16, 16, 0.3), rgba(255, 255, 255, 0.3));
}

::scroll-button(*):active {
  border-style: inset;
}

::scroll-button(*):active:disabled {
  border-style: outset;
}

::scroll-button(*):focus-visible {
  outline: auto 1px -webkit-focus-ring-color;
}
)BlinkUA";

// IDR_UASTYLE_SCROLL_MARKER_CSS: third_party/blink/renderer/core/css/scroll_marker.css
constexpr char kResource8[] = R"BlinkUA(
::scroll-marker,
::column::scroll-marker {
  color: -webkit-link;
  text-decoration: underline;
  cursor: pointer;
}

::scroll-marker:active,
::column::scroll-marker:active {
  color: -webkit-activelink
}

::scroll-marker:focus-visible,
::column::scroll-marker:focus-visible {
  outline: auto 1px -webkit-focus-ring-color;
  outline-offset: 1px;
}
)BlinkUA";

// IDR_UASTYLE_CAPABILITY_ELEMENT_CSS: third_party/blink/renderer/core/html/resources/capability_element.css
constexpr char kResource9[] = R"BlinkUA(
/*
 * Copyright 2023 The Chromium Authors
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * The default style sheet used to render <permission> elements
 * (require PermissionElement enabled).
 */

@namespace "http://www.w3.org/1999/xhtml";

permission, geolocation, install, usermedia {
  background-color: ButtonFace;
  border: solid 1px ButtonBorder;
  box-sizing: content-box !important;
  border-radius: 3px;
  color: ButtonText;
  cursor: pointer;
  display: inline-block;
  font-weight: normal;
  font-style: normal;
  padding: 8px 16px;
  height: auto;
  width: auto;
  word-spacing: normal;
  vertical-align: middle !important;
 }

permission:granted {
  background-color: white;
}

permission::-internal-permission-text, geolocation::-internal-permission-text, install::-internal-permission-text, usermedia::-internal-permission-text {
  text-emphasis: initial !important;
  text-shadow: initial !important;
  align-items: center;
  display: flex;
  font-family: Arial, Helvetica, sans-serif;
  font-size: inherit;
  font-style: inherit;
  font-weight: inherit;
  height: fit-content;
  width: fit-content;
  hyphenate-character: auto;
  line-height: normal;
  min-height: inherit;
  max-height: inherit;
  outline: none;
  user-select:none;
  white-space:nowrap;
  word-wrap: normal;
  word-spacing: inherit;
  -webkit-text-security: none !important;
}

permission::-internal-permission-container, geolocation::-internal-permission-container, install::-internal-permission-container, usermedia::-internal-permission-container {
  display: flex;
  flex-flow: row nowrap;
  justify-content: center;
  align-items: center;
  height: 100%;
  width: fit-content;
  min-height: inherit;
  max-height: inherit;
  margin: auto;
  text-indent: 0px;
}

permission::permission-icon, geolocation::permission-icon, install::permission-icon, usermedia::permission-icon {
  fill: currentcolor;
  height: 1.3em;
  width: auto;
  margin-inline-end: 5px;
  margin-block-start: 0px !important;
  margin-block-end: 0px !important;
  margin-inline-start: 0px !important;
}
)BlinkUA";

// IDR_UASTYLE_THEME_INPUT_MULTIPLE_FIELDS_CSS: third_party/blink/renderer/core/html/resources/input_multiple_fields.css
constexpr char kResource10[] = R"BlinkUA(
/* Copyright 2014 The Chromium Authors
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* This sheet is appended to html.css before parsing which means the selectors
   below are in the default html namespace:

   @namespace "http://www.w3.org/1999/xhtml"
*/

input[type="date" i],
input[type="datetime-local" i],
input[type="month" i],
input[type="time" i],
input[type="week" i] {
    font-family: monospace;
    padding: 0;
    padding-inline-start: 1px;
    cursor: default;
}

input::-webkit-datetime-edit {
    flex: 1;
    min-width: 0;
    -webkit-user-modify: read-only !important;
    display: inline-block;
    overflow: hidden;
}

input::-internal-datetime-container {
    display: flex;
    align-items: center;
}

input::-webkit-datetime-edit-fields-wrapper {
    -webkit-user-modify: read-only !important;
    display: inline-block;
    padding: 1px 0;
    white-space: pre;
}

/* If you update padding, border, or margin in the following ruleset, update
   DateTimeFieldElement::maximumWidth too. */
input::-webkit-datetime-edit-ampm-field,
input::-webkit-datetime-edit-day-field,
input::-webkit-datetime-edit-hour-field,
input::-webkit-datetime-edit-millisecond-field,
input::-webkit-datetime-edit-minute-field,
input::-webkit-datetime-edit-month-field,
input::-webkit-datetime-edit-second-field,
input::-webkit-datetime-edit-week-field,
input::-webkit-datetime-edit-year-field {
    -webkit-user-modify: read-only !important;
    border: none;
    display: inline;
    font: inherit !important;
    padding: 1px;
}

/* If you update padding, border, or margin in the following ruleset, update
   DateTimeEditElement::customStyelForRenderer too. */
input::-webkit-datetime-edit-text {
    -webkit-user-modify: read-only !important;
    display: inline;
    font: inherit !important;
}

input[type="date" i]::-webkit-inner-spin-button,
input[type="datetime" i]::-webkit-inner-spin-button,
input[type="datetime-local" i]::-webkit-inner-spin-button,
input[type="month" i]::-webkit-inner-spin-button,
input[type="time" i]::-webkit-inner-spin-button,
input[type="week" i]::-webkit-inner-spin-button {
    /* FIXME: Remove height. */
    height: 1.5em;
    margin-inline-start: 2px;
}
)BlinkUA";

// IDR_UASTYLE_THEME_FORCED_COLORS_CSS: third_party/blink/renderer/core/html/resources/forced_colors.css
constexpr char kResource11[] = R"BlinkUA(
/* Copyright 2019 The Chromium Authors
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* These forced colors mode styles override the default styling for HTML
 * elements as defined in core/html/resources/html.css when forced colors mode
 * is enabled.
 */

/* This sheet is appended to html.css before parsing which means the selectors
   below are in the default html namespace:

   @namespace "http://www.w3.org/1999/xhtml"
*/

@media ua-forced-colors {
  :focus-visible {
    -internal-forced-outline-color: Highlight;
  }

  a:link,
  a:-webkit-any-link:active {
    -internal-forced-color: LinkText;
  }

  a:visited {
    -internal-forced-color: VisitedText;
  }

  fieldset {
    -internal-forced-border-color: CanvasText;
  }

  mark {
    -internal-forced-background-color: yellow;
    -internal-forced-color: black;
  }

  ::placeholder {
    -internal-forced-color: GrayText;
  }

  input,
  textarea {
    background-color: Canvas;
    -internal-forced-background-color: Canvas;
    -internal-forced-border-color: ButtonText;
    -internal-forced-color: CanvasText;
  }

  input:hover,
  textarea:hover,
  input[type="file"]:hover::-webkit-file-upload-button,
  input:focus,
  textarea:focus {
    -internal-forced-border-color: Highlight;
  }

  input[type="text"]:disabled,
  input[type="password"]:disabled,
  input[type="email"]:disabled,
  input[type="number"]:disabled,
  input[type="tel"]:disabled,
  input[type="url"]:disabled,
  input[type="search"]:disabled,
  input[type="date"]:disabled,
  input[type="month"]:disabled,
  input[type="week"]:disabled,
  input[type="time"]:disabled,
  input[type="datetime-local"]:disabled,
  textarea:disabled {
    background-color: ButtonFace;
    -internal-forced-background-color: ButtonFace;
    -internal-forced-border-color: GrayText;
    -internal-forced-color: GrayText;
  }

  input::-webkit-calendar-picker-indicator {
    background-color: ButtonFace;
    -internal-forced-background-color: ButtonFace;
    -internal-forced-color: ButtonText;
  }

  input::-webkit-datetime-edit-ampm-field:focus,
  input::-webkit-datetime-edit-day-field:focus,
  input::-webkit-datetime-edit-hour-field:focus,
  input::-webkit-datetime-edit-millisecond-field:focus,
  input::-webkit-datetime-edit-minute-field:focus,
  input::-webkit-datetime-edit-month-field:focus,
  input::-webkit-datetime-edit-second-field:focus,
  input::-webkit-datetime-edit-week-field:focus,
  input::-webkit-datetime-edit-year-field:focus {
      background-color: Highlight;
      outline: none;
      -internal-forced-background-color: Highlight;
      -internal-forced-color: HighlightText;
  }

  input[type="color"]:disabled {
    border-color: GrayText;
  }

  input[type="color"] {
    forced-color-adjust: none;
  }

  input[type="color"]::-webkit-color-swatch {
    border-color: CanvasText !important;
  }

  button,
  input[type="button"],
  input[type="submit"],
  input[type="reset"],
  input[type="file"]::-webkit-file-upload-button {
    background-color: ButtonFace;
    -internal-forced-background-color: ButtonFace;
    -internal-forced-border-color: ButtonBorder;
    -internal-forced-color: ButtonText;
  }

  button:hover,
  input[type="button"]:hover,
  input[type="submit"]:hover,
  input[type="reset"]:hover,
  button:focus,
  input[type="button"]:focus,
  input[type="submit"]:focus,
  input[type="reset"]:focus {
    -internal-forced-border-color: Highlight;
  }

  button:disabled,
  input[type="button"]:disabled,
  input[type="submit"]:disabled,
  input[type="reset"]:disabled {
    -internal-forced-border-color: GrayText;
    -internal-forced-color: GrayText;
  }

  /* same color as hyperlinks */
  details summary {
    -internal-forced-color: LinkText;
  }

  select:-internal-list-box {
    background-color: Canvas !important;
    -internal-forced-background-color: Canvas !important;
    -internal-forced-border-color: ButtonText;
  }

  /* option disabled */
  select:-internal-list-box option:disabled,
  select:-internal-list-box option:disabled:hover,
  select:-internal-list-box:disabled option,
  select:-internal-list-box:disabled option:hover {
    background-color: Canvas !important;
    -internal-forced-background-color: Canvas !important;
    color: GrayText !important;
  }

  /* option selected */
  select:-internal-list-box:focus option:checked,
  select:-internal-list-box:focus option:checked:hover,
  select:-internal-list-box:focus option:checked:enabled:hover,
  select:-internal-list-box option:checked,
  select:-internal-list-box option:checked:hover,
  select:-internal-list-box:enabled option:checked:enabled:hover {
    background-color: Highlight !important;
    color: HighlightText !important;
    forced-color-adjust: none;
  }

  /* option both disabled and selected */
  select:-internal-list-box:focus option:checked:disabled,
  select:-internal-list-box:focus option:checked:disabled:hover,
  select:-internal-list-box:disabled option:checked,
  select:-internal-list-box:disabled option:checked:hover,
  select:-internal-list-box option:checked:disabled,
  select:-internal-list-box option:checked:disabled:hover {
    background-color: GrayText !important;
    color: Canvas !important;
    forced-color-adjust: none;
  }

  select:-internal-list-box option:hover {
    background-color: Highlight !important;
    color: HighlightText !important;
    forced-color-adjust: none;
  }

  select {
    background-color: Canvas;
    -internal-forced-background-color: Canvas;
    -internal-forced-border-color: CanvasText;
    -internal-forced-color: CanvasText;
  }

  select:not(:-internal-list-box) {
    background-color: Canvas;
    -internal-forced-background-color: Canvas;
  }

  select:hover {
    -internal-forced-border-color: Highlight;
  }

  select:focus {
    -internal-forced-border-color: Highlight;
  }

  select:disabled {
    opacity: 1;
    -internal-forced-border-color: GrayText;
    -internal-forced-color: GrayText;
  }

  meter::-webkit-meter-bar {
    background-color: ButtonFace;
    -internal-forced-background-color: ButtonFace;
    -internal-forced-border-color: CanvasText;
  }

  meter::-webkit-meter-even-less-good-value,
  meter::-webkit-meter-optimum-value,
  meter::-webkit-meter-suboptimum-value {
    background-color: Highlight;
    -internal-forced-background-color: Highlight;
  }

  input:-internal-autofill-previewed,
  textarea:-internal-autofill-previewed,
  select:-internal-autofill-previewed {
    background-color: Canvas !important;
    -internal-forced-background-color: Canvas !important;
    -internal-forced-color: CanvasText !important;
  }

  input:-internal-autofill-selected,
  textarea:-internal-autofill-selected,
  select:-internal-autofill-selected {
    background-color: Canvas !important;
    -internal-forced-background-color: Canvas !important;
    -internal-forced-color: CanvasText !important;
  }

  /* The duplicated :not(:-internal-list-box):not([multiple]) is to ensure specificity over
   * another stylesheet. TODO(crbug.com/378869807): Replace this with at-rules to
   * ensure correct specificity. */
  select:not(:-internal-list-box):not([multiple]):not(:-internal-list-box):not([multiple]) {
    background-color: -internal-auto-base(Canvas, color-mix(currentColor 10%, transparent));
  }

  /* Undoes opacity: -internal-auto-base(0.7, unset) from html.css */
  select:not(:-internal-list-box):not([multiple]):not(:-internal-list-box):not([multiple]):disabled {
    opacity: 1;
  }
}
)BlinkUA";

// IDR_UASTYLE_SVG_CSS: third_party/blink/renderer/core/css/svg.css
constexpr char kResource12[] = R"BlinkUA(
/*
 * The default style sheet used to render SVG.
 *
 * Copyright (C) 2005, 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

@namespace "http://www.w3.org/2000/svg";

/*
    When an outermost SVG 'svg' element is stand-alone or embedded inline within a parent XML grammar 
    which does not use CSS layout [CSS2-LAYOUT] or XSL formatting [XSL], the 'overflow' property on the 
    outermost 'svg' element is ignored for the purposes of visual rendering and the initial clipping path is set 
    to the bounds of the initial viewport.

    When an outermost 'svg' element is embedded inline within a parent XML grammar which uses CSS layout
    [CSS2-LAYOUT] or XSL formatting [XSL], if the 'overflow' property has the value hidden or scroll, then
    the user agent will establish an initial clipping path equal to the bounds of the initial viewport; otherwise,
    the initial clipping path is set according to the clipping rules as defined in [CSS2-overflow].

    Opera/Firefox & WebKit agreed on NOT setting "overflow: hidden" for a root svg element - SVG 1.1 Errata
    contains these changes as well as all future SVG specifications: see http://lists.w3.org/Archives/Public/public-svg-wg/2008JulSep/0347.html
    Note that here "root svg element" means when <svg> is the document element. (":root" in CSS parlance.)
    LayoutSVGRoot objects embedded within containing content get overflow: hidden by default.
    https://svgwg.org/svg2-draft/single-page.html#render-OverflowAndClipProperties
*/

svg:not(:root), symbol, image, marker, pattern, foreignObject {
    overflow: hidden
}

svg:not(:root) {
  overflow-clip-margin: content-box;
}

svg:root {
    width: 100%;
    height: 100%;
}

text, foreignObject {
    display: block
}

text {
   white-space: nowrap
}

a:-webkit-any-link {
  cursor: pointer;
}

tspan, textPath {
   white-space: inherit
}

/* states */

:focus {
    outline: auto 5px -webkit-focus-ring-color
}

/*
   CSS transform specification:
   "For SVG elements without associated CSS layout box the initial used value is '0 0'".
*/

*:not(svg), *:not(foreignObject) > svg {
    transform-origin: 0 0;
}

/*
   This is added as to not break SVG content in forced colors mode:
   https://drafts.csswg.org/css-color-adjust-1/#forced-colors-properties
*/
@media ua-forced-colors {
  svg {
      forced-color-adjust: preserve-parent-color;
  }

  foreignObject {
      forced-color-adjust: auto;
  }
}
)BlinkUA";

// IDR_UASTYLE_MARKER_CSS: third_party/blink/renderer/core/css/marker.css
constexpr char kResource13[] = R"BlinkUA(
::marker, ::before::marker, ::after::marker {
  unicode-bidi: isolate;
  font-variant-numeric: tabular-nums;
  text-transform: none;
  text-indent: 0 !important;
  text-align: start !important;
  text-align-last: auto !important;
}
)BlinkUA";

// IDR_UASTYLE_MATHML_CSS: third_party/blink/renderer/core/css/mathml.css
constexpr char kResource14[] = R"BlinkUA(
/*
 * The default style sheet used to render MathML.
 *
 * Copyright (C) 2014 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

@namespace url(http://www.w3.org/1998/Math/MathML);

/* Universal rules */
* {
  font-size: math;
  display: block math;
  writing-mode: horizontal-tb !important;
}

/* The <math> element */
math {
  direction: ltr;
  text-indent: 0;
  letter-spacing: normal;
  line-height: normal;
  word-spacing: normal;
  font-family: math;
  font-size: inherit;
  font-style: normal;
  font-weight: normal;
  display: inline math;
  math-shift: normal;
  math-style: compact;
  math-depth: 0;
}
math[display="block" i] {
  display: block math;
  math-style: normal;
}
math[display="inline" i] {
  display: inline math;
  math-style: compact;
}

:focus {
    outline: auto 1px -webkit-focus-ring-color;
}

/* <mrow>-like elements */
semantics > :not(:first-child) {
  display: none;
}
maction > :not(:first-child) {
  display: none;
}
merror {
  border: 1px solid red;
  background-color: lightYellow;
}
mphantom {
  visibility: hidden;
}

/* Token elements */
mi {
  text-transform: math-auto;
}

/* Tables */
mtable {
  display: inline-table;
  math-style: compact;
}
mtr {
  display: table-row;
}
mtd {
  display: table-cell;
  /* Centering inside table cells should rely on box alignment properties.
     See https://github.com/w3c/mathml-core/issues/156 */
  text-align: -webkit-center;
  padding: 0.5ex 0.4em;
}

/* Fractions */
mfrac {
  padding-inline-start: 1px;
  padding-inline-end: 1px;
}
mfrac > * {
  math-depth: auto-add;
  math-style: compact;
}
mfrac > :nth-child(2) {
  math-shift: compact;
}

/* Other rules for scriptlevel, displaystyle and math-shift */
mroot > :not(:first-child) {
  math-depth: add(2);
  math-style: compact;
}
mroot, msqrt {
  math-shift: compact;
}
msub > :not(:first-child),
msup > :not(:first-child),
msubsup > :not(:first-child),
mmultiscripts > :not(:first-child),
munder > :not(:first-child),
mover > :not(:first-child),
munderover > :not(:first-child) {
  math-depth: add(1);
  math-style: compact;
}
munder[accentunder="true" i] > :nth-child(2),
mover[accent="true" i] > :nth-child(2),
munderover[accentunder="true" i] > :nth-child(2),
munderover[accent="true" i] > :nth-child(3) {
  font-size: inherit;
}
msub > :nth-child(2),
msubsup > :nth-child(2),
mmultiscripts > :nth-child(even),
mmultiscripts > mprescripts ~ :nth-child(odd),
mover[accent="true" i] > :first-child,
munderover[accent="true" i] > :first-child {
  math-shift: compact;
}
mmultiscripts > mprescripts ~ :nth-child(even) {
  math-shift: inherit;
}
)BlinkUA";

// IDR_UASTYLE_FULLSCREEN_CSS: third_party/blink/renderer/core/css/fullscreen.css
constexpr char kResource15[] = R"BlinkUA(
:not(:root):fullscreen, :xr-overlay {
  position: fixed !important;
  inset: 0 !important;
  margin: 0 !important;
  box-sizing: border-box !important;
  min-width: 0 !important;
  max-width: none !important;
  min-height: 0 !important;
  max-height: none !important;
  width: 100% !important;
  height: 100% !important;
  transform: none !important;

  /* intentionally not !important */
  object-fit: contain;
  user-select: text;
}

/* Reducing specificity to ensure [inert] UA rule overrides this one for the
   interactivity declaration. */
:where(:fullscreen) {
  overlay: auto !important;
  interactivity: auto;
}

iframe:fullscreen {
  border: none !important;
  padding: 0 !important;
}

/* TODO(foolip): In the spec, there's a ::backdrop block with the properties
   shared with dialog::backdrop (see html.css). */
:not(:root):fullscreen::backdrop {
  position: fixed;
  inset: 0;
  background: black;
}

@media (vertical-viewport-segments: 2) {
  :not(:root):fullscreen {
    height: env(viewport-segment-bottom 0 0, 100%) !important;
    width: 100% !important;
  }
}

@media (horizontal-viewport-segments: 2) {
  :not(:root):fullscreen {
    height: 100% !important;
    width: env(viewport-segment-right 0 0, 100%) !important;
  }
}

/* Anything below are extensions over what the Fullscreen API (29 May 2018) mandates. */

/* This prevents video from overflowing the viewport in
   virtual/android/fullscreen/video-scrolled-iframe.html (crbug.com/441890) and
   removes scrollbars caused by html { overflow: scroll } (crbug.com/543946).
   TODO(foolip): This is done differently in Gecko, find a fix not involving the
   ancestor selector in https://github.com/whatwg/fullscreen/issues/19. */
:root:-webkit-full-screen-ancestor {
  overflow: hidden !important;
}

:fullscreen:-internal-video-persistent-ancestor :not(:-internal-video-persistent-ancestor) {
  display: none !important;
}

:-internal-video-persistent {
  position: fixed !important;
  left: 0 !important;
  top: 0 !important;
  margin: 0 !important;
  min-width: 0 !important;
  max-width: none !important;
  min-height: 0 !important;
  max-height: none !important;
  width: 100% !important;
  height: 100% !important;
  transform: none !important;

  background-color: black !important;
  z-index: 2147483647 !important;
}

:xr-overlay {
  /* force a transparent background */
  background: rgba(0,0,0,0) !important;

  /* act as containing block for descendants */
  contain: paint !important;
}
)BlinkUA";

// IDR_UASTYLE_TRANSITION_CSS: third_party/blink/renderer/core/css/transition.css
constexpr char kResource16[] = R"BlinkUA(
/*
 * Copyright 2022 The Chromium Authors
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * The default style sheet used for view transitions.
 * See third_party/blink/renderer/core/view_transition/README.md for details
 */

@namespace "http://www.w3.org/1999/xhtml";

/*
 * Rules for the global view transition user agent style sheet defined in:
 * https://drafts.csswg.org/css-view-transitions-2/#ua-styles
 *
 * Note, only rules affecting pseudo-elements are defined here. Rules
 * for view-transition-related properties on elements (e.g. for
 * view-transition-group and view-transition-name) are in html.css.
 */

::view-transition {
  position: absolute;
  inset: 0;
}

::view-transition-group(*) {
  position: absolute;
  top: 0;
  left: 0;

  animation-duration: 0.25s;
  animation-fill-mode: both;
}

::view-transition-image-pair(*) {
  position: absolute;
  inset: 0;
}

::view-transition-old(*),
::view-transition-new(*) {
  position: absolute;
  display: block;
  inset-block-start: 0;
  inline-size: 100%;
  block-size: auto;
}

::view-transition-image-pair(*),
::view-transition-old(*),
::view-transition-new(*),
::view-transition-group-children(*) {
  animation-duration: inherit;
  animation-fill-mode: inherit;
  animation-delay: inherit;
  animation-timing-function: inherit;
  animation-iteration-count: inherit;
  animation-direction: inherit;
  animation-play-state: inherit;
}

::view-transition-group-children(*) {
  position: absolute;
  inset: 0;
  border-style: solid;
  border-color: transparent;
}

/* Missing from css-view-transitions-2/#ua-styles */
::view-transition-group-children(*) {
  animation-duration: inherit;
  animation-fill-mode: inherit;
}
)BlinkUA";

// IDR_UASTYLE_OVERSCROLL_CSS: third_party/blink/renderer/core/css/overscroll.css
constexpr char kResource17[] = R"BlinkUA(
::-internal-overscroll-area-parent(*) {
  display: block;
  inset: 0;
  overflow: auto;
  pointer-events: none;
  scroll-behavior: inherit;
  scroll-snap-type: both mandatory;
  scrollbar-width: none;
  position: absolute;
}
)BlinkUA";

// IDR_UASTYLE_JSON_DOCUMENT_CSS: third_party/blink/renderer/core/css/json-document.css
constexpr char kResource18[] = R"BlinkUA(
/* Copyright 2024 The Chromium Authors
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. */

body > pre {
  padding-top: 20px;
  word-wrap: break-word;
  white-space: pre-wrap;
}
.json-formatter-container {
  position: fixed;
  top: 0px;
  width: 100%;
}
body {
  margin: 0;
}
.json-formatter-container::-internal-json-formatter-control {
  width: 100%;
  font-size: initial;
  font-family: monospace;
  user-select: none;
  background-color: light-dark(rgb(240, 240, 240),rgb(60, 60, 60));
  border-bottom: 1px solid rgb(187, 187, 187);
  display: flex;
  justify-content: flex-start;
  align-items: center;
}

)BlinkUA";

String FromStaticUtf8(const char* data, size_t size) {
  return String::FromUtf8(std::string_view(data, size));
}

}  // namespace

String UncompressResourceAsASCIIString(int resource_id) {
  switch (resource_id) {
    case IDR_UASTYLE_HTML_CSS:
      return FromStaticUtf8(kResource0, sizeof(kResource0) - 1);
    case IDR_UASTYLE_QUIRKS_CSS:
      return FromStaticUtf8(kResource1, sizeof(kResource1) - 1);
    case IDR_UASTYLE_VIEW_SOURCE_CSS:
      return FromStaticUtf8(kResource2, sizeof(kResource2) - 1);
    case IDR_UASTYLE_THEME_CHROMIUM_ANDROID_CSS:
      return FromStaticUtf8(kResource3, sizeof(kResource3) - 1);
    case IDR_UASTYLE_FULLSCREEN_ANDROID_CSS:
      return FromStaticUtf8(kResource4, sizeof(kResource4) - 1);
    case IDR_UASTYLE_THEME_CHROMIUM_LINUX_CSS:
      return FromStaticUtf8(kResource5, sizeof(kResource5) - 1);
    case IDR_UASTYLE_THEME_MAC_CSS:
      return FromStaticUtf8(kResource6, sizeof(kResource6) - 1);
    case IDR_UASTYLE_SCROLL_BUTTON_CSS:
      return FromStaticUtf8(kResource7, sizeof(kResource7) - 1);
    case IDR_UASTYLE_SCROLL_MARKER_CSS:
      return FromStaticUtf8(kResource8, sizeof(kResource8) - 1);
    case IDR_UASTYLE_CAPABILITY_ELEMENT_CSS:
      return FromStaticUtf8(kResource9, sizeof(kResource9) - 1);
    case IDR_UASTYLE_THEME_INPUT_MULTIPLE_FIELDS_CSS:
      return FromStaticUtf8(kResource10, sizeof(kResource10) - 1);
    case IDR_UASTYLE_THEME_FORCED_COLORS_CSS:
      return FromStaticUtf8(kResource11, sizeof(kResource11) - 1);
    case IDR_UASTYLE_SVG_CSS:
      return FromStaticUtf8(kResource12, sizeof(kResource12) - 1);
    case IDR_UASTYLE_MARKER_CSS:
      return FromStaticUtf8(kResource13, sizeof(kResource13) - 1);
    case IDR_UASTYLE_MATHML_CSS:
      return FromStaticUtf8(kResource14, sizeof(kResource14) - 1);
    case IDR_UASTYLE_FULLSCREEN_CSS:
      return FromStaticUtf8(kResource15, sizeof(kResource15) - 1);
    case IDR_UASTYLE_TRANSITION_CSS:
      return FromStaticUtf8(kResource16, sizeof(kResource16) - 1);
    case IDR_UASTYLE_OVERSCROLL_CSS:
      return FromStaticUtf8(kResource17, sizeof(kResource17) - 1);
    case IDR_UASTYLE_JSON_DOCUMENT_CSS:
      return FromStaticUtf8(kResource18, sizeof(kResource18) - 1);
    default:
      return String();
  }
}

}  // namespace blink
