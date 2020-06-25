THREE.DefaultDragControls = function ( _object, _camera, _domElement ) {
	var _plane = new THREE.Plane();
	var _raycaster = new THREE.Raycaster();

	var _mouse = new THREE.Vector2();
	var _offset = new THREE.Vector3();
	var _intersection = new THREE.Vector3();

	var _draging = false;
	var _hovered = null;

	var scope = this;

	function activate() {

		_domElement.addEventListener( 'mousemove', onDocumentMouseMove, false );
		_domElement.addEventListener( 'mousedown', onDocumentMouseDown, false );
		_domElement.addEventListener( 'mouseup', onDocumentMouseCancel, false );
		_domElement.addEventListener( 'mouseleave', onDocumentMouseCancel, false );
		_domElement.addEventListener( 'touchmove', onDocumentTouchMove, false );
		_domElement.addEventListener( 'touchstart', onDocumentTouchStart, false );
		_domElement.addEventListener( 'touchend', onDocumentTouchEnd, false );

	}

	function deactivate() {

		_domElement.removeEventListener( 'mousemove', onDocumentMouseMove, false );
		_domElement.removeEventListener( 'mousedown', onDocumentMouseDown, false );
		_domElement.removeEventListener( 'mouseup', onDocumentMouseCancel, false );
		_domElement.removeEventListener( 'mouseleave', onDocumentMouseCancel, false );
		_domElement.removeEventListener( 'touchmove', onDocumentTouchMove, false );
		_domElement.removeEventListener( 'touchstart', onDocumentTouchStart, false );
		_domElement.removeEventListener( 'touchend', onDocumentTouchEnd, false );

	}

	function dispose() {

		deactivate();

	}

	function onDocumentMouseMove( event ) {

		event.preventDefault();

		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

		_raycaster.setFromCamera( _mouse, _camera );

		if ( _draging && scope.enabled && _object ) {

			if ( _raycaster.ray.intersectPlane( _plane, _intersection ) ) {

				_object.position.copy( _intersection.sub( _offset ) );

			}

			scope.dispatchEvent( { type: 'drag', object: _object } );

			return;

		}

		_raycaster.setFromCamera( _mouse, _camera );

		_plane.setFromNormalAndCoplanarPoint( _camera.getWorldDirection( _plane.normal ), _object.position );

		if ( _hovered !== _object ) {

			scope.dispatchEvent( { type: 'hoveron', object: _object } );

			_domElement.style.cursor = 'pointer';
			_hovered = _object;

		}

		if ( _hovered !== null ) {

			scope.dispatchEvent( { type: 'hoveroff', object: _hovered } );

			_domElement.style.cursor = 'auto';
			_hovered = null;

		}

	}

	function onDocumentMouseDown( event ) {

		event.preventDefault();

		_draging = true;

		_raycaster.setFromCamera( _mouse, _camera );

		if ( _raycaster.ray.intersectPlane( _plane, _intersection ) ) {

			_offset.copy( _intersection ).sub( _object.position );

		}

		_domElement.style.cursor = 'move';

		scope.dispatchEvent( { type: 'dragstart', object: _object } );

	}

	function onDocumentMouseCancel( event ) {

		event.preventDefault();

		if ( _draging && _object ) {

			scope.dispatchEvent( { type: 'dragend', object: _object } );

			_draging = false;

		}

		_domElement.style.cursor = 'auto';

	}

	function onDocumentTouchMove( event ) {

		event.preventDefault();

		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

		_raycaster.setFromCamera( _mouse, _camera );

		if ( _draging && scope.enabled && _object ) {

			if ( _raycaster.ray.intersectPlane( _plane, _intersection ) ) {

				_object.position.copy( _intersection.sub( _offset ) );

			}

			scope.dispatchEvent( { type: 'drag', object: _object } );

			return;

		}

	}

	function onDocumentTouchStart( event ) {

		event.preventDefault();

		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

		_raycaster.setFromCamera( _mouse, _camera );

		if ( _raycaster.ray.intersectPlane( _plane, _intersection ) ) {

			_offset.copy( _intersection ).sub( _object.position );

		}

		_domElement.style.cursor = 'move';

		scope.dispatchEvent( { type: 'dragstart', object: _object } );

	}

	function onDocumentTouchEnd( event ) {

		event.preventDefault();

		if ( _draging ) {

			scope.dispatchEvent( { type: 'dragend', object: _object } );

			_draging = false;

		}

		_domElement.style.cursor = 'auto';

	}

	activate();
	
	// API

	this.enabled = true;

	this.activate = activate;
	this.deactivate = deactivate;
	this.dispose = dispose;

	// Backward compatibility

	this.setObjects = function () {

		console.error( 'THREE.DefaultDragControls: setObjects() has been removed.' );

	};

	this.on = function ( type, listener ) {

		console.warn( 'THREE.DefaultDragControls: on() has been deprecated. Use addEventListener() instead.' );
		scope.addEventListener( type, listener );

	};

	this.off = function ( type, listener ) {

		console.warn( 'THREE.SimpleRotationControls: off() has been deprecated. Use removeEventListener() instead.' );
		scope.removeEventListener( type, listener );

	};

	this.notify = function ( type ) {

		console.error( 'THREE.DefaultDragControls: notify() has been deprecated. Use dispatchEvent() instead.' );
		scope.dispatchEvent( { type: type } );

	};

};

THREE.DefaultDragControls.prototype = Object.create( THREE.EventDispatcher.prototype );
THREE.DefaultDragControls.prototype.constructor = THREE.DefaultDragControls;
