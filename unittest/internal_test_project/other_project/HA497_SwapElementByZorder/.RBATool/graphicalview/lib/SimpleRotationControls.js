/**
 * Copied from DragControls.js and updated to support rotation of objects
 */

THREE.SimpleRotationControls = function ( _objects, _camera, _domElement ) {

	if ( _objects instanceof THREE.Camera ) {

		console.warn( 'THREE.SimpleRotationControls: Constructor now expects ( objects, camera, domElement )' );
		var temp = _objects; _objects = _camera; _camera = temp;

	}

	var _plane = new THREE.Plane();
	var _raycaster = new THREE.Raycaster();

	var _mouse = new THREE.Vector2();
	var _offset = new THREE.Vector3();
	var _intersection = new THREE.Vector3();

    var _selected = null, _hovered = null;
    
    var _previousMousePosition = {
        x: 0,
        y: 0
    };

	//

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

		if ( _selected && scope.enabled ) {

            //_selected.rotation.y = (event.offsetX - _mouse.x) / 30.0;
            //_selected.rotation.x = (event.offsetY - _mouse.y) / 30.0;
            
            var deltaMove = {
                x: event.offsetX - _previousMousePosition.x,
                y: event.offsetY - _previousMousePosition.y
            };


            var deltaRotationQuaternion = new THREE.Quaternion()
                .setFromEuler(new THREE.Euler(
                    toRadian(deltaMove.y * 1),
                    toRadian(deltaMove.x * 1),
                    0,
                    'XYZ'
                ));

            _selected.quaternion.multiplyQuaternions(deltaRotationQuaternion, _selected.quaternion);

            _previousMousePosition = {
                x: event.offsetX,
                y: event.offsetY
            }

			scope.dispatchEvent( { type: 'rotate', object: _selected } );

			return;
        } 
        
		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

		_raycaster.setFromCamera( _mouse, _camera );

		_raycaster.setFromCamera( _mouse, _camera );

		var intersects = _raycaster.intersectObjects( _objects );

		if ( intersects.length > 0 ) {

			var object = intersects[ 0 ].object;

			_plane.setFromNormalAndCoplanarPoint( _camera.getWorldDirection( _plane.normal ), object.position );

			if ( _hovered !== object ) {

				scope.dispatchEvent( { type: 'hoveron', object: object } );

				_domElement.style.cursor = 'pointer';
				_hovered = object;

			}

		} else {

			if ( _hovered !== null ) {

				scope.dispatchEvent( { type: 'hoveroff', object: _hovered } );

				_domElement.style.cursor = 'auto';
				_hovered = null;

			}

		}

	}

	function onDocumentMouseDown( event ) {

        event.preventDefault();

        _previousMousePosition = {
            x: event.offsetX,
            y: event.offsetY
        }

		_raycaster.setFromCamera( _mouse, _camera );

		var intersects = _raycaster.intersectObjects( _objects );

		if ( intersects.length > 0 ) {

			_selected = intersects[ 0 ].object;

			if ( _raycaster.ray.intersectPlane( _plane, _intersection ) ) {

				_offset.copy( _intersection ).sub( _selected.position );

			}

			_domElement.style.cursor = 'move';

			scope.dispatchEvent( { type: 'rotatestart', object: _selected } );

		}


	}

	function onDocumentMouseCancel( event ) {

		event.preventDefault();

		if ( _selected ) {

			scope.dispatchEvent( { type: 'rotateend', object: _selected } );

			_selected = null;

		}

		_domElement.style.cursor = 'auto';

	}

	function onDocumentTouchMove( event ) {

		event.preventDefault();
		event = event.changedTouches[ 0 ];

		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

		_raycaster.setFromCamera( _mouse, _camera );

		if ( _selected && scope.enabled ) {

			//_selected.rotation.y = (event.offsetX - _mouse.x) / 30.0;
            //_selected.rotation.x = (event.offsetY - _mouse.y) / 30.0;
            
            var deltaMove = {
                x: event.offsetX - _previousMousePosition.x,
                y: event.offsetY - _previousMousePosition.y
            };

            var deltaRotationQuaternion = new THREE.Quaternion()
                .setFromEuler(new THREE.Euler(
                    toRadian(deltaMove.y * 1),
                    toRadian(deltaMove.x * 1),
                    0,
                    'XYZ'
                ));

            _selected.quaternion.multiplyQuaternions(deltaRotationQuaternion, _selected.quaternion);

            _previousMousePosition = {
                x: event.offsetX,
                y: event.offsetY
            }

			scope.dispatchEvent( { type: 'rotate', object: _selected } );

			return;
		}

	}

	function onDocumentTouchStart( event ) {

		event.preventDefault();
		event = event.changedTouches[ 0 ];

		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

		_raycaster.setFromCamera( _mouse, _camera );

		var intersects = _raycaster.intersectObjects( _objects );

		if ( intersects.length > 0 ) {

            _selected = intersects[ 0 ].object;

			_plane.setFromNormalAndCoplanarPoint( _camera.getWorldDirection( _plane.normal ), _selected.position );

			if ( _raycaster.ray.intersectPlane( _plane, _intersection ) ) {

				_offset.copy( _intersection ).sub( _selected.position );

			}

			_domElement.style.cursor = 'move';

			scope.dispatchEvent( { type: 'rotatestart', object: _selected } );

		}


	}

	function onDocumentTouchEnd( event ) {

		event.preventDefault();

		if ( _selected ) {

			scope.dispatchEvent( { type: 'rotateend', object: _selected } );

			_selected = null;

		}

		_domElement.style.cursor = 'auto';

	}

	function setSelectionToParentGroup() {
		while (_selected.parent && _selected.parent.type === 'Group') {
			_selected = _selected.parent;
		}
	}

	activate();

	// API

	this.enabled = true;

	this.activate = activate;
	this.deactivate = deactivate;
	this.dispose = dispose;
	this.setSelectionToParentGroup = setSelectionToParentGroup;

	// Backward compatibility

	this.setObjects = function () {

		console.error( 'THREE.SimpleRotationControls: setObjects() has been removed.' );

	};

	this.on = function ( type, listener ) {

		console.warn( 'THREE.SimpleRotationControls: on() has been deprecated. Use addEventListener() instead.' );
		scope.addEventListener( type, listener );

	};

	this.off = function ( type, listener ) {

		console.warn( 'THREE.SimpleRotationControls: off() has been deprecated. Use removeEventListener() instead.' );
		scope.removeEventListener( type, listener );

	};

	this.notify = function ( type ) {

		console.error( 'THREE.SimpleRotationControls: notify() has been deprecated. Use dispatchEvent() instead.' );
		scope.dispatchEvent( { type: type } );

	};

};

function toRadian(angle) {
    return angle * (Math.PI / 180);
}

function toDegree(angle) {
    return angle * (180 / Math.PI);
}

THREE.SimpleRotationControls.prototype = Object.create( THREE.EventDispatcher.prototype );
THREE.SimpleRotationControls.prototype.constructor = THREE.SimpleRotationControls;
