THREE.LabelControls = function(_objects, _camera, _domElement) {
  if (_objects instanceof THREE.Camera) {
    var temp = _objects;
    _objects = _camera;
    _camera = temp;
  }

  var _plane = new THREE.Plane();
  var _raycaster = new THREE.Raycaster();

  var _mouse = new THREE.Vector2();
  var _offset = new THREE.Vector3();
  var _intersection = new THREE.Vector3();

  var label = document.createElement("div");
  label.style.padding = "5px";
  label.style.border = "2px solid green";
  label.style.backgroundColor = 'white';
  label.style.color = "black";
  label.style.position = "absolute";
  label.style.textAlign = "center";
  label.style.zIndex = 100;
  label.style.display = "block";
  label.style.minWidth = "200px";
  label.style.textAlign = "left";
  label.classList.add('unselectable');

  var canvasWrapper = document.getElementById('canvasWrapper');
  canvasWrapper.appendChild(label);

  label.style.top = '10px';//event.clientY + "px";
  label.style.left = '10px'; //event.clientX + "px";

  //

  var scope = this;

  function activate() {
    _domElement.addEventListener("mousemove", onDocumentMouseMove, false);
  }

  function deactivate() {
    _domElement.removeEventListener("mousemove", onDocumentMouseMove, false);
  }

  function dispose() {
    deactivate();
  }

  function onDocumentMouseMove(event) {
    //event.preventDefault();

    var rect = _domElement.getBoundingClientRect();

    _mouse.x = (event.clientX - rect.left) / rect.width * 2 - 1;
    _mouse.y = -((event.clientY - rect.top) / rect.height) * 2 + 1;

    _raycaster.setFromCamera(_mouse, _camera);

    var intersects = _raycaster.intersectObjects(_objects);

    if (intersects.length > 0 && scope.enabled) {
      var firstObject = intersects[0].object;
      if (firstObject.type === 'area') {
        label.innerHTML = `Area Name: ${firstObject.name}`;
        scope.dispatchEvent({ type: "label", object: firstObject });
        return;
      }

      for (var i = 1; i < intersects.length; i++) {
        var object = intersects[i].object;
        if (object.type === 'area' && object.parentLayer === firstObject) {
          if (firstObject === 'layer' && object.parentLayer !== firstObject) {
            label.innerHTML = 'Area Name: ';
            return;
          }
          label.innerHTML = `Area Name: ${object.name}`;
          scope.dispatchEvent({ type: "label", object: object });
          return;
        }
      }
    }

    label.innerHTML = 'Area Name: ';

  }

  activate();

  // API

  this.enabled = true;

  this.activate = activate;
  this.deactivate = deactivate;
  this.dispose = dispose;
};

THREE.LabelControls.prototype = Object.create(THREE.EventDispatcher.prototype);
THREE.LabelControls.prototype.constructor = THREE.LabelControls;
