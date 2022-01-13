<template>
<div class="home">
  <a class="footer" href="https://github.com/JMorre">GitHub</a>
</div>

</template>

<script>
// @ is an alias to /src

export default {
  name: 'home',
  components: {

  },
  computed: {
    photos() {
      return this.$store.state.photos;
    }
  },
  async created() {
    await this.$store.dispatch("getAllPhotos");
  },
}
</script>

<style scoped>
a.footer {
  position: fixed;
  bottom: 0;
  left: 0;
  width: 100%;
  padding: 10px 16px;
  text-decoration: none;
  background-color: #c10000;
  color: #efefef;
  font-size: 14px;
  font-family: "Palatino Linotype";
}
</style>
