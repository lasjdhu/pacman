(self.webpackChunk_N_E=self.webpackChunk_N_E||[]).push([[405],{1276:function(e,t,n){(window.__NEXT_P=window.__NEXT_P||[]).push(["/",function(){return n(34126)}])},34126:function(e,t,n){"use strict";n.r(t),n.d(t,{__N_SSP:function(){return i},default:function(){return l}});var r=n(39324),u=n(35250),o=n(21172),a=n(97873),i=!0;function l(e){return(0,a.sT)("CHATGPT_PRIMARY"),(0,u.jsx)(o.default,(0,r._)({},e))}},97873:function(e,t,n){"use strict";n.d(t,{n3:function(){return i},sT:function(){return a}});var r=n(35250);function u(){return"CHATGPT_HYBRID"}function o(e){var t=u();return"CHATGPT_HYBRID"===t||"CHATGPT_HYBRID"===e||e===t}function a(e){if(!o(e))throw console.error("Server mode does not support this page. Server: ".concat(u()," Requested mode: ").concat(e)),Error("Server mode does not support this endpoint")}function i(e){var t=e.mode,n=e.children;return o(t)?(0,r.jsx)(r.Fragment,{children:n}):(console.error("Server mode does not support this page. Server: ".concat(u()," Requested mode: ").concat(t)),(0,r.jsx)(r.Fragment,{}))}n(70079)},21654:function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0});var r=n(39324),u=n(71209);Object.defineProperty(t,"__esModule",{value:!0}),function(e,t){for(var n in t)Object.defineProperty(e,n,{enumerable:!0,get:t[n]})}(t,{noSSR:function(){return l},default:function(){return d}});var o=n(64838),a=(n(70079),o._(n(1905)));function i(e){return{default:(null==e?void 0:e.default)||e}}function l(e,t){return delete t.webpack,delete t.modules,e(t)}function d(e,t){var n=a.default,o={loading:function(e){return e.error,e.isLoading,e.pastDelay,null}};e instanceof Promise?o.loader=function(){return e}:"function"==typeof e?o.loader=e:"object"==typeof e&&(o=r._({},o,e));var d=(o=r._({},o,t)).loader;return(o.loadableGenerated&&(o=r._({},o,o.loadableGenerated),delete o.loadableGenerated),"boolean"!=typeof o.ssr||o.ssr)?n(u._(r._({},o),{loader:function(){return null!=d?d().then(i):Promise.resolve(i(function(){return null}))}})):(delete o.webpack,delete o.modules,l(n,o))}("function"==typeof t.default||"object"==typeof t.default&&null!==t.default)&&void 0===t.default.__esModule&&(Object.defineProperty(t.default,"__esModule",{value:!0}),Object.assign(t.default,t),e.exports=t.default)},48326:function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),Object.defineProperty(t,"LoadableContext",{enumerable:!0,get:function(){return r}});var r=n(64838)._(n(70079)).default.createContext(null)},1905:function(e,t,n){"use strict";Object.defineProperty(t,"__esModule",{value:!0});var r=n(51217),u=n(31819),o=n(39324),a=n(71209);Object.defineProperty(t,"__esModule",{value:!0}),Object.defineProperty(t,"default",{enumerable:!0,get:function(){return m}});var i=n(64838)._(n(70079)),l=n(48326),d=[],s=[],c=!1;function f(e){var t=e(),n={loading:!0,loaded:null,error:null};return n.promise=t.then(function(e){return n.loading=!1,n.loaded=e,e}).catch(function(e){throw n.loading=!1,n.error=e,e}),n}var _=function(){function e(t,n){r._(this,e),this._loadFn=t,this._opts=n,this._callbacks=new Set,this._delay=null,this._timeout=null,this.retry()}return u._(e,[{key:"promise",value:function(){return this._res.promise}},{key:"retry",value:function(){var e=this;this._clearTimeouts(),this._res=this._loadFn(this._opts.loader),this._state={pastDelay:!1,timedOut:!1};var t=this._res,n=this._opts;t.loading&&("number"==typeof n.delay&&(0===n.delay?this._state.pastDelay=!0:this._delay=setTimeout(function(){e._update({pastDelay:!0})},n.delay)),"number"==typeof n.timeout&&(this._timeout=setTimeout(function(){e._update({timedOut:!0})},n.timeout))),this._res.promise.then(function(){e._update({}),e._clearTimeouts()}).catch(function(t){e._update({}),e._clearTimeouts()}),this._update({})}},{key:"_update",value:function(e){this._state=o._(a._(o._({},this._state),{error:this._res.error,loaded:this._res.loaded,loading:this._res.loading}),e),this._callbacks.forEach(function(e){return e()})}},{key:"_clearTimeouts",value:function(){clearTimeout(this._delay),clearTimeout(this._timeout)}},{key:"getCurrentValue",value:function(){return this._state}},{key:"subscribe",value:function(e){var t=this;return this._callbacks.add(e),function(){t._callbacks.delete(e)}}}]),e}();function p(e){return function(e,t){var n=function(){if(!a){var t=new _(e,o);a={getCurrentValue:t.getCurrentValue.bind(t),subscribe:t.subscribe.bind(t),retry:t.retry.bind(t),promise:t.promise.bind(t)}}return a.promise()},r=function(){n();var e=i.default.useContext(l.LoadableContext);e&&Array.isArray(o.modules)&&o.modules.forEach(function(t){e(t)})},u=function(e,t){r();var n=i.default.useSyncExternalStore(a.subscribe,a.getCurrentValue,a.getCurrentValue);return i.default.useImperativeHandle(t,function(){return{retry:a.retry}},[]),i.default.useMemo(function(){var t;return n.loading||n.error?i.default.createElement(o.loading,{isLoading:n.loading,pastDelay:n.pastDelay,timedOut:n.timedOut,error:n.error,retry:a.retry}):n.loaded?i.default.createElement((t=n.loaded)&&t.default?t.default:t,e):null},[e,n])},o=Object.assign({loader:null,loading:null,delay:200,timeout:null,webpack:null,modules:null},t),a=null;if(!c){var d=o.webpack?o.webpack():o.modules;d&&s.push(function(e){var t=!0,r=!1,u=void 0;try{for(var o,a=d[Symbol.iterator]();!(t=(o=a.next()).done);t=!0){var i=o.value;if(-1!==e.indexOf(i))return n()}}catch(e){r=!0,u=e}finally{try{t||null==a.return||a.return()}finally{if(r)throw u}}})}return u.preload=function(){return n()},u.displayName="LoadableComponent",i.default.forwardRef(u)}(f,e)}function h(e,t){for(var n=[];e.length;){var r=e.pop();n.push(r(t))}return Promise.all(n).then(function(){if(e.length)return h(e,t)})}p.preloadAll=function(){return new Promise(function(e,t){h(d).then(e,t)})},p.preloadReady=function(e){return void 0===e&&(e=[]),new Promise(function(t){var n=function(){return c=!0,t()};h(s,e).then(n,n)})},window.__NEXT_PRELOADREADY=p.preloadReady;var m=p},70060:function(e,t,n){e.exports=n(21654)}},function(e){e.O(0,[786,960,246,798,931,432,734,774,888,179],function(){return e(e.s=1276)}),_N_E=e.O()}]);