// Copyright (c) 2018 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

const glob = require("glob");
const path = require("path");
const TerserPlugin = require('terser-webpack-plugin');

const __firefox__ = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/__firefox__.js")[0];

const AllFramesAtDocumentStart = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/AllFrames/AtDocumentStart/*.js");
const AllFramesAtDocumentStartSandboxed = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/Sandboxed/AllFrames/AtDocumentStart/*.js");
const AllFramesAtDocumentEnd = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/AllFrames/AtDocumentEnd/*.js");
const AllFramesAtDocumentEndSandboxed = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/Sandboxed/AllFrames/AtDocumentEnd/*.js");

const MainFrameAtDocumentStart = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/MainFrame/AtDocumentStart/*.js");
const MainFrameAtDocumentEnd = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/MainFrame/AtDocumentEnd/*.js");
const MainFrameAtDocumentStartSandboxed = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/Sandboxed/MainFrame/AtDocumentStart/*.js");
const MainFrameAtDocumentEndSandboxed = glob.sync("./ios/brave-ios/Sources/Brave/Frontend/UserContent/UserScripts/Sandboxed/MainFrame/AtDocumentEnd/*.js");

module.exports = {
  mode: "production",
  entry: {
    "__firefox__": __firefox__,
    AllFramesAtDocumentStart: AllFramesAtDocumentStart,
    AllFramesAtDocumentStartSandboxed: AllFramesAtDocumentStartSandboxed,
    AllFramesAtDocumentEnd: AllFramesAtDocumentEnd,
    AllFramesAtDocumentEndSandboxed: AllFramesAtDocumentEndSandboxed,
    MainFrameAtDocumentStart: MainFrameAtDocumentStart,
    MainFrameAtDocumentEnd: MainFrameAtDocumentEnd,
    MainFrameAtDocumentStartSandboxed: MainFrameAtDocumentStartSandboxed,
    MainFrameAtDocumentEndSandboxed: MainFrameAtDocumentEndSandboxed
  },
  // optimization: { minimize: false }, // use for debugging
  output: {
    filename: "[name].js",
    path: path.resolve(__dirname, "Sources/Brave/Assets")
  },
  optimization: {
    minimize: true,
    minimizer: [
      new TerserPlugin({
        extractComments: false,
        terserOptions: {
          format: {
            comments: false,
          },
        },
      }),
    ],
  },
  module: {
    rules: []
  },
  plugins: []
};
